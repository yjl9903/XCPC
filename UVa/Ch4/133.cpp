#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int cnt, n, k, m, p[100] = { 0 };

int go(int tot, int k, int d)
{
	while (k--)
	{
		do
		{
			tot = (tot + d + n - 1) % n + 1;
		} while (p[tot] == -1);
	}
	return tot;
}
int main()
{
	while (cin >> n >> k >> m && n && m && k)
	{
		int t1 = 0, t2 = n + 1, kase = 0;
		cnt = n;
		for (int i = 0; i <= n; i++)
			p[i] = i;

		while (cnt)
		{
			t1 = go(t1, k, 1);
			t2 = go(t2, m, -1);

			if (kase++)
				cout << ',';

			if ((t1 + n) % n == (t2 + n) % n)
			{
				cnt--;
				cout << setw(3) << p[(t1 + n - 1) % n + 1];
			}
			else
			{
				cnt -= 2;
				cout << setw(3) << p[(t1 + n - 1) % n + 1];
				cout << setw(3) << p[(n + t2 - 1) % n + 1];
			}
			p[(t1 + n - 1) % n + 1] = -1;
			p[(n + t2 - 1) % n + 1] = -1;
		}
		cout << endl;
	}
}