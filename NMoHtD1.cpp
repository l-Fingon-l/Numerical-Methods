#include <cmath> 
#include <iostream> 
#include <cstdio>
#include <iomanip> 
#include "Function.h"

#define LN 0  
#define Linear 1  
#define Lagrange 2  
#define Derivative_1 3 
#define Derivative_2 4 
#define X_ 5

using namespace std;

double x_min = -1.5;
double x_max = 1.5;
double h = 0.12;
int amount_ = 9;
double* x = new double[amount_];
double* y = new double[amount_];

double linear(double x, double* x_original, double* y_original)
{
	int n = 0;
	double result = 0;
	while (x >= x_original[n]) n++;
	result = y_original[n - 1] * ((x - x_original[n]) / (x_original[n - 1] - x_original[n])) +
		y_original[n] * ((x - x_original[n - 1]) / (x_original[n] - x_original[n - 1]));
	return result;
}

double ln_(double x) //f(x)=ln(x^4-2*x^2+3)  
{
	double result = log(x*x*x*x - 2 * x*x + 3);
	return result;
}

double lagrange(double X, double* x, double* y)
{
	double result = 0, Ln = 0;
	for (int i(0); i < amount_; i++)
	{
		Ln = y[i];
		for (int j(0); j < i; j++)
		{
			Ln *= (X - x[j]) / (x[i] - x[j]);
		}
		for (int j(i + 1); j < amount_; j++)
		{
			Ln *= (X - x[j]) / (x[i] - x[j]);
		}
		result += Ln;
	}
	return result;
}

double right_derivative(double y1, double y2, double h)
{
	return ((y2 - y1) / h);
}

double left_derivative(double y1, double y2, double h)
{
	return ((y2 - y1) / h);
}

double central_derivative(double y1, double y2, double h)
{
	return ((y2 - y1) / 2 * h);
}

double derivative_1(double xxx)
{
	int n = ((x_max - x_min) / h) + 1;
	double** y1 = function(x_min, x_max, h, x, y);
	double* dy = new double[n];
	for (int i(0); i < n; i++)
	{
		if (i == 0) dy[i] = right_derivative(y1[1][i], y1[1][i + 1], h);
		else if (i == (n - 1)) dy[i] = left_derivative(y1[1][i - 1], y1[1][i], h);
		else dy[i] = central_derivative(y1[1][i - 1], y1[1][i + 1], h);
	}
	int j = 0;
	while (xxx != y1[0][j]) j++;
	return dy[j];

	delete[] y1[1];
	delete[] y1[0];
	delete[] y1;
	delete[] dy;
}

double second_derivative(double y1, double y2, double y3, double h)
{
	return ((y1 + y3 - 2 * y2) / h * h);
}

double derivative_2(double xxx)
{
	int n = ((x_max - x_min) / h) + 1;
	double** y1 = function(x_min, x_max, h, x, y);
	double* d2y = new double[n - 2];
	for (int i(0); i < (n - 2); i++)
	{
		d2y[i] = second_derivative(y1[1][i - 1], y1[1][i], y1[1][i + 1], h);
	}
	int j = 0;
	if (xxx == y1[0][0]) return 0;
	if (xxx == y1[0][n - 1]) return 0;
	while (xxx != y1[0][j]) j++;
	return d2y[j];

	delete[] y1[1];
	delete[] y1[0];
	delete[] y1;
	delete[] d2y;
}

double choice(double x, double* x_original, double* y_original, int c)
{
	double result = 0;
	switch (c)
	{
	case 0: result = ln_(x);
		break;
	case 1: result = linear(x, x_original, y_original);
		break;
	case 2: result = lagrange(x, x_original, y_original);
		break;
	case 3: result = derivative_1(x);
		break;
	case 4: result = derivative_2(x);
		break;
	case 5: result = ln_(x);
	}
	return result;
}

double** Function(double x_min, double x_max, double h, double* x, double* y, int c)
{
	int n = ((x_max - x_min) / h) + 1;
	double** ln = new double*[2];
	ln[0] = new double[n]; // x  
	ln[1] = new double[n]; // y  

	double temp = x_min;
	for (int i(0); i < n; i++)
	{
		ln[0][i] = temp;
		ln[1][i] = choice(temp, x, y, c);
		for (int k(0); k < n; k++)
		{
			if (temp == x[k] && (c <= 2)) ln[1][i] = y[k];
		}
		temp += h;
	}
	return ln;
}

double Tasks(int c, int number)
{
	double** y1 = Function(x_min, x_max, h, x, y, c);

	if (c == 5) return y1[0][number];
	return y1[1][number];
	delete[] y1[0];
	delete[] y1[1];
	delete[] y1;
}

int main()
{
	// defining the given data  
	x[0] = -1.6;
	x[1] = -1.1;
	x[2] = -0.6;
	x[3] = -0.2;
	x[4] = 0.2;
	x[5] = 0.7;
	x[6] = 0.93;
	x[7] = 1.2;
	x[8] = 1.51;
	//  
	y[0] = 1.48921;
	y[1] = 0.71496;
	y[2] = 0.87946;
	y[3] = 1.07213;
	y[4] = 1.07213;
	y[5] = 0.81541;
	y[6] = 0.70223;
	y[7] = 0.78554;
	y[8] = 1.29161;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
	//double** y1 = Interpolation(x_min, x_max, h, x, y, c);  
	int n = ((x_max - x_min) / h) + 1;
	cout << setw(12) << left << "x" << setw(12) << "f(x)" << setw(12) << "linear" << setw(12) << "lagrange"
		<< setw(12) << "deriv_1" << setw(12) << "deriv_2" << endl << endl;
	for (int i(0); i < n; i++)
	{
		cout << setprecision(3) << setw(12) << left << Tasks (X_, i) << setw(12) << Tasks(LN, i) << setw(12) 
			<< Tasks(Linear, i) << setw(12) << Tasks(Lagrange, i) << setw(12) << Tasks(Derivative_1, i)
			<< setw(12) << Tasks(Derivative_2, i) << endl << endl;
	}

	delete[] x;
	delete[] y;
	system("PAUSE");
	return 0;
}