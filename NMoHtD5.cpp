#include <cstdio>
#include <iostream>
#include <iomanip>

#define E 0.0001
#define h 0.1

using namespace std;

double * gauss(double **a, double *y, int n)
{
	double *x, max;
	int k, index;
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < E)
		{
			// нет ненулевых диагональных элементов
			cout << "Решение получить невозможно из-за нулевого столбца ";
			cout << index << " матрицы A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < E) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}


int main()
{
	double x = 0, t = 0, **a, *b, *y;
	int  n = 1 / h;
	a = new double*[n + 3];
	b = new double[n + 3];
	for (int i(0); i <= n + 2; i++)
	{
		a[i] = new double[n + 3];
	}
	a[0][0] = -0.6 / h;
	a[0][1] = 1;
	a[0][2] = 0.6 / h;
	for (int i(3); i <= n + 2; i++)
		a[0][i] = 0;
	b[0] = 2;
	a[n + 2][n] = -1 / (2 * h);
	a[n + 2][n + 1] = 0;
	a[n + 2][n + 2] = 1 / (2 * h);
	for (int i(0); i < n; i++)
		a[n + 2][i] = 0;
	b[n + 2] = 1;

	for (int i(1); i < n + 2; i++)
	{
		for (int j(0); j <= i - 2; j++)
			a[i][j] = 0;
		a[i][i - 1] = 1 / (h*h) + 1 / (4 * h);
		a[i][i] = -2 / (h*h) + 0.8;
		a[i][i + 1] = 1 / (h*h) - 1 / (4 * h);
		for (int j(i + 2); j <= n + 2; j++)
			a[i][j] = 0;
		b[i] = (i - 1)*h;
	}

	y = gauss(a, b, n + 3);
	cout << "\nThe results with accuracy " << E << ":" << endl << endl;
	for (int i(1); i < n + 2; i++)
	{
		t = (i - 1)*h;
		x = t * (0.3) + 1.7;
		cout << "y(" << (i - 1)*h << ") = "<< setprecision(4) << y[i] << endl;
	}
	system("PAUSE");
    return 0;
}

