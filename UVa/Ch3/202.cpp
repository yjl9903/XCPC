#include <iostream>
#include <cstring>
using namespace std;
int digit[3010];
int f[3010];
int rest[3010];

int main()
{
	int m, n;
	while (cin >> m >> n)
	{
		memset(f, 0, sizeof(f));
		memset(rest, 0, sizeof(rest));
		memset(digit, 0, sizeof(digit));
		int count = 0;
		digit[count++] = m / n;
		cout << m << '/' << n << " = " << digit[0] << '.';
		m = m % n;
		while (m && !f[m])
		{
			f[m] = count;
			rest[count] = m;
			digit[count++] = 10 * m / n;
			m = 10 * m % n;
		}
		int i = 1, ans;
		while (rest[i] != m)
			cout << digit[i++];
		ans = i;
		cout << '(' << digit[i++];
		while (rest[i] != m && i != count)
			if (i - ans == 50)
			{
				cout << "...";
				break;
			}
			else
				cout << digit[i++];
		cout << ')' << endl << "   " << ((count - ans) ? (count - ans) : 1) << " = number of digits in repeating cycle" << endl << endl;
	}
	return 0;
}