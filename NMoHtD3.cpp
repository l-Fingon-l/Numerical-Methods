#include <cstdio>
#include <iostream>
#include <iomanip>

#define E 0.0001
#define k 2

using namespace std;

double g(double x)
{
	return (cos(x)/k + (x - x/k));
}

double dx(double x)
{
	return ((1 - 1 / k) - sin(x) / k);
}

double MotSI(double a, double b) // method of the simple iterations
{
	if (abs(dx(a)) > 1 || abs(dx(b)) > 1)
	{
		cout << "Choose another K" << endl;
		system("PAUSE");
	}
	double x1 = a, x2 = g(x1);
	int n = 1;
	while(abs(x2 - x1) > E)
	{
		x1 = x2;
		x2 = g(x1);
		n++;
	}
	cout << "done " << n << " iterations" << endl;
	return x2;
}

int main()
{
	double a = 0, b = 2, x = 0;
	x = MotSI(a, b);

	cout << "x = " << setprecision(4) << x << " with accuracy " << E << endl << endl;

	system("PAUSE");
    return 0;
}

