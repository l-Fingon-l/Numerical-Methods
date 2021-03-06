#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

const double h = 0.1, t_min = 0, t_max = 0.5, x_min = 0, x_max = 1, T = 0.1, M = 1;
int n = (x_max - x_min) / h;
int m = (t_max - t_min) / T;

double u_i_jj(double u_i_j, double u_ii_j, double u_j, double u_i) // cross
{
	return 2 * (1 - T * T * M * M / (h*h))*u_i_j + T * T * M * M / (h*h)*(u_ii_j + u_j) - u_i;
}
double x(int n)
{
	return x_min + n * h;
}
double t(int n)
{
	return t_min + n * T;
}
double f(double x)
{
	return 1.2*x - x * x;
}
double F(double x)
{
	return (x + 0.6)*sin(x);
}
double a(double t)
{
	return 0;
}
double A(double t)
{
	return 0.2 + 0.5*t;
}

int main()
{
	double **u = new double*[m + 1];
	for (int j(0); j <= m; j++) u[j] = new double[n + 1];

	for (int i(0); i <= n; i++) u[0][i] = f(x(i)); // 0 level
	for (int i(0); i <= n; i++) u[1][i] = u[0][i] + T * F(x(i)) + T * T / 2 * (-2); // 1-st level
	for (int j(1); j <= m; j++) u[j][0] = a(t(j)); // lower corner
	for (int j(1); j <= m; j++) u[j][n] = A(t(j)); // upper corner

	for (int i(1); i < n; i++)
		for (int j(1); j < m; j++) u[j + 1][i] = u_i_jj(u[j][i], 
			u[j][i + 1], u[j][i - 1], u[j - 1][i]); // filling the desicion

	for (int i(0); i <= n; i++)
	{
		for (int j(0); j <= m; j++) cout << setw(12) << left << setprecision(4) << u[j][i];
		cout << endl;
	}

	system("PAUSE");
    return 0;
}

