#include <cstdio>
#include <iostream>
#include <iomanip>

#define E 0.0001
#define k1 1.1
#define k3 3
//x3'=3*x3
//x1'=1.1*x1
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
/*

double g1(double x1,double x2, double x3, double x4)
{
	return (2.07*x2 - 0.62*k3*x3 - 3.22)/(2.06*k1);
}
double g2(double x1, double x2, double x3, double x4)
{
	return (-3.17*k1*x1 + 1.23*k3*x3 +2.18*x4)/4.28;
}
double g3(double x1, double x2, double x3, double x4)
{
	return (-0.98*k1*x1 - 3.12*x2 + 1.2*x4 + 2.16)/1.1*k3;
}
double g4(double x1, double x2, double x3, double x4)
{
	return (2.06*k1*x1 +3.14*x2 +0.97*k3*x3 + 6.11)/3.15;
}

/*bool M(double x1, double x2, double x3, double x4)
{
	double m1 = 0, m2 = 0, m3 = 0, m4 = 0;
	m1 = 1 - 5.23/(0.5*5.23*k) + 2.21 / (0.5*5.23*k) + 0.61 / (0.5*5.23*k) + 2.18 / (0.5*5.23*k);
	m2 = 1 - 5.21/(0.5*5.21*k) + 0.35 / (0.5*5.21*k) + 3.15 / (0.5*5.21*k);
	m3 = 1 - 0.62/(0.5*0.62*k) + 2.06 / (0.5*0.62*k) + 2.07 / (0.5*0.62*k);
	m4 = 1 - 1.2/(0.5*1.2*k) + 0.98 / (0.5*1.2*k) + 3.12 / (0.5*1.2*k) + 1.1 / (0.5*1.2*k);
	if (m1 < 1 && m2 < 1 && m3 < 1 && m4 < 1) return true;
	else return false;
}*/
/*
void Method_of_Seidel(double *a, double *b, double *c, double *d) 
{
//	if (M(*a, *b, *c, *d) == false)
//	{
	//	cout << "Choose another g(x)" << endl;
	//	system("PAUSE");
//	}
	double x1 = *a, x2 = *b, x3 = *c, x4 = *d, y1 = g1(x1, x2, x3, x4);
	double y2 = g2(y1, x2, x3, x4), y3 = g3(y1, y2, x3, x4), y4 = g4(y1, y2, y3, x4);
	int n = 1;
	while (abs(y1 - x1) > E && abs(y2 - x2)  > E && abs(y3 - x3)  > E && abs(y4 - x4) > E)
	{
		x1 = y1;
		x2 = y2;
		x3 = y3;
		x4 = y4;
		y1 = g1(x1, x2, x3, x4);
		y2 = g2(y1, x2, x3, x4);
		y3 = g3(y1, y2, x3, x4);
		y4 = g4(y1, y2, y3, x4);
		n++;
	}
	*a = y1/k1;
	*b = y2;
	*c = y3/k3;
	*d = y4;
	cout << "done " << n << " iterations" << endl;
}
*/
int main()
{
	double **a, *b, *y;
	a = new double*[4];
	for (int i(0); i < 4; i++)
		a[i] = new double[4];
	for (int i(0); i < 4; i++)
		for (int j(0); j < 4; j++)
		{
			cout << "a[" << i << "][" << j << "] = ";
			cin >> a[i][j];
		}
	b = new double[4];
	b[0] = -3.22;
	b[1] = -6.11;
	b[2] = 0;
	b[3] = 2.16;
	y = new double[4];
	y = gauss(a, b, 4);

	for (int i(0); i < 4; i++)
		cout << "x" << i + 1 << " = " << y[i] << endl;
	system("PAUSE");
	/*
	double x1 = -3.22/(2.06*k1), x2 = 0.5, x3 = 2.16/(1.1*k3), x4 = 6.11/3.15;
	Method_of_Seidel(&x1, &x2, &x3, &x4);

	cout << "x1 = " << setprecision(4) << x1 << endl <<
		"x2 = " << setprecision(4) << x2 << endl <<
		"x3 = " << setprecision(4) << x3 << endl <<
		"x4 = " << setprecision(4) << x4 << endl << " with accuracy " << E << endl << endl;
		*/
	system("PAUSE");
	return 0;
}

