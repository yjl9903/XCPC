#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	char s[20];
	while (scanf("%s", s) == 1 && s != "0e0")
	{
		int a, c;
		long long b;

		sscanf(s, "%d.%llde%d", &a, &b, &c);
		//sscanf(s, "%f", &m);
		//printf("%d %lld %d", a, b, c);
		double m = a + b / pow(10, 15);
		//printf("%f", m);
		int x = 1, y = 1, sum = 1;

		double M[20][40];
		long long E[20][40];
		for (int i = 0; i < 10; i++)
			for (int j = 1; j < 31; j++)
			{
				double m = 1 - 1.0 / (1 << (i + 1));
				double e = ((1 << j) - 1);
				double t = log10(m) + e * log10(2);;
				E[i][j] = t / 1;
				M[i][j] = pow(10, t - E[i][j]);
			}

		while (m < 1)
		{
			m *= 10;
			c--;
		}

		//double t = log10(m) + c;
		int flag = 0;
		for (int j = 1; j < 31; j++)
		{
			for (int i = 0; i < 10; i++)
				if (c == E[i][j] && m < M[i][j])
				{
					cout << i << ' ' << j << endl;
					flag = 1;
					break;
				}
			if (flag)	break;
		}
	}
	return 0;
}