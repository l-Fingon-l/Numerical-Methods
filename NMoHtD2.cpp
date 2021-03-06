#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>

#define E 0.0001
#define N 5 // the first amount of particles
#define hx 0.1 // in main

using namespace std;

double function(double x)
{
	double result = 0;
	result = (x * x + 1) / (x * x * x * x + x * x + 1);
	return result;
}

double trapeze(double x_min, double x_max, int n)
{
	double result = 0;
	double h = (x_max - x_min) / n;
	double* x = new double[n + 1];
	x[0] = x_min;
	for (int i(1); i <= n; i++)
	{
		x[i] = x[i - 1] + h;
	}
	for (int i(1); i < n; i++)
	{
		result += 2 * function(x[i]);
	}
	result += function(x[0]) + function(x[n]);
	result *= h / 2;

	return result;
}

double integral(double x_min, double x_max, double accuracy)
{
	double I1 = 0, I2 = 0;
	int n = N;
	do
	{
		I1 = trapeze(x_min, x_max, n);
		n *= 2;
		I2 = trapeze(x_min, x_max, n);
	} while (abs((I2 - I1) / 3) > accuracy);

	return I2;
}

int main()
{
	double x_min = 0, x_max = 1;
	int n = (x_max - x_min) / hx + 1;
	double** y = new double*[2];
	y[0] = new double[n];
	y[1] = new double[n];
	y[0][0] = 0;
	y[1][0] = integral(x_min, y[0][0], E);
	for (int i(1); i < n; i++)
	{
		y[0][i] = y[0][i - 1] + hx;
		y[1][i] = integral(x_min, y[0][i], E);
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cout << setw(10) << left << "X" << setw(10) << "F(X)" << endl << endl;
	for (int i(0); i < n; i++)
	{
		cout << setw(10) << left << y[0][i] << setw(10) << setprecision(4) << y[1][i] << endl;
	}
	
	system("PAUSE");
    return 0;
}

