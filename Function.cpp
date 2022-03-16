#include "Function.h"

double linear_(double x, double* x_original, double* y_original)
{
	int n = 0;
	double result = 0;
	while (x >= x_original[n]) n++;
	result = y_original[n - 1] * ((x - x_original[n]) / (x_original[n - 1] - x_original[n])) +
		y_original[n] * ((x - x_original[n - 1]) / (x_original[n] - x_original[n - 1]));
	return result;
}

double** function(double x_min, double x_max, double h, double* x, double* y)
{
	int n = ((x_max - x_min) / h) + 1;
	double** ln = new double*[2];
	ln[0] = new double[n]; // x  
	ln[1] = new double[n]; // y  

	double temp = x_min;
	for (int i(0); i < n; i++)
	{
		ln[0][i] = temp;
		ln[1][i] = linear_(temp, x, y);
		for (int k(0); k < n; k++)
		{
			if (temp == x[k]) ln[1][i] = y[k];
		}
		temp += h;
	}
	return ln;
}
