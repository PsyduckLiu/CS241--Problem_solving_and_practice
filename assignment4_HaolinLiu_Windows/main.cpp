#include <iostream>
#include <math.h>
using namespace std;

class error {};
class nosolution {};

int Judge(double **b, int num)
{
	int i, j, k;
	double temp;
	double *tmp;
	tmp = new double[num + 1];

	for (k = 0; k < num; k++)
	{
		double max = 0;
		int line = k;
		for (i = k; i < num; i++)
		{
			if (fabs(b[i][k]) > max) {
				max = fabs(b[i][k]);
				line = i;
			}
		}

		if (b[line][k] == 0) return 0;

		if (k != line) {
			for (i = 0; i <= num; i++) {
				tmp[i] = b[k][i];
				b[k][i] = b[line][i];
				b[line][i] = tmp[i];
			}
		}

		for (i = k + 1; i < num; i++) {

			temp = b[i][k] / b[k][k];
			for (j = 0; j <= num; j++) {
				b[i][j] = b[i][j] - temp * b[k][j];
			}
		}
	}

	return 1;
}

void GaussianElimination(double **b, int num)
{
	int i, j, k;
	double temp;
	double *tmp;
	tmp = new double[num + 1];

	for (k = 0; k < num; k++)
	{
		double max = 0;
		int line = 0;
		for (i = k; i < num; i++)
		{
			if (fabs(b[i][k]) > max) {
				max = fabs(b[i][k]);
				line = i;
			}
		}

		if (k != line) {
			for (i = 0; i <= num; i++) {
				tmp[i] = b[k][i];
				b[k][i] = b[line][i];
				b[line][i] = tmp[i];
			}
		}

		for (i = k + 1; i < num; i++) {
			temp = b[i][k] / b[k][k];
			for (j = 0; j <= num; j++) {
				b[i][j] = b[i][j] - temp * b[k][j];
			}
		}
	}

	for (i = 0; i <= num; i++) {
		tmp[i] = 0;
	}

	for (i = num - 1; i >= 0; i--) {
		temp = 0;
		for (k = 0; k < num; k++) {
			temp = temp + tmp[k] * b[i][k];
		}

		tmp[i] = (b[i][num] - temp) / b[i][i];

	}

	cout << endl << "Results is:" << endl;
	for (i = 0; i < num; i++) {
		cout << tmp[i] << ' ';
	}

	delete []tmp;
}

void JacobiIteration(double **b, int num, double *x)
{
	int i, j, k, step = 0;
	double tmp, *y;
	y = new double[num];

	for (k = 0;; k++) {
		for (i = 0; i < num; i++) {
			y[i] = x[i];
		}

		for (i = 0; i < num; i++) {
			tmp = 0.0;
			for (j = 0; j < num; j++) {
				if (i == j) continue;
				tmp += b[i][j] * y[j];
			}
			x[i] = (b[i][num] - tmp) / b[i][i];
		}

		for (i = 0, j = 0; i < num; i++) {
			if (fabs(y[i] - x[i]) < 0.001) j++;
	    }

		if (j == num) break;

		if (k == 9999) {
			cout << "Maximum number of iterations exceeded!";
			step = 1;
			break;
		}
	}
    if (step == 0) {
	  cout << endl << "Results is:" << endl;
	  for (i = 0; i < num; i++) {
		  cout << x[i] << ' ';
	  }
    }

	delete []y;
}


int main()
{
	int n,method;
	double **a,*x,**b;
	int i,j;

    try {
		cout << "Input the number of equations and unknowns n:";
	    cin >> n;
		if (cin.fail() == 1) throw error();

	    x = new double[n];
	    a = new double*[n];
	    for (i = 0; i < n; i++) a[i] = new double[n + 1];
		b = new double*[n];
		for (i = 0; i < n; i++) b[i] = new double[n + 1];

		cout << endl;
        cout << "Input the augmented matrix of Ax=b as [A b]:" << endl;
	    for (i = 0; i < n; i++) {
		for (j = 0; j <= n; j++) {
			cin >> a[i][j];
		}
		if (cin.fail() == 1) throw error();
	    }
		for (i = 0; i < n; i++) {
			for (j = 0; j <= n; j++) {
				b[i][j] = a[i][j];
			}
		}

		if (Judge(b,n) == 0) throw nosolution();

		cout << endl;
		cout << "[0] Jacobi Iteration [1] Gaussian Elimination" << endl;
		cout << "Choose a method:";
		cin >> method;

		if (method == 0) {
			cout << endl << "Input the initial approximationg x(0):";
			for (i = 0; i < n; i++) {
				cin >> x[i];
			}
			JacobiIteration(a, n, x);
		}

		else {
			GaussianElimination(a, n);
		}

		for (i = 0; i < n; i++) {
			delete[] a[i];
		}
		delete[]a;
		delete[]x;
	}
	catch (error) { cout << "Invalid input!"; }
	catch (nosolution) { cout << "No unique solution exists!"; }
system("pause");

return 0;
}

