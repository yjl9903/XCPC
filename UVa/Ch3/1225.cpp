#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int count[10];
		memset(count, 0, sizeof(count));
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			int x = i;
			while (x)
			{
				count[x % 10]++;
				x /= 10;
			}
		}
		for (int i = 0; i < 9; i++)
		{
			cout << count[i] << ' ';
		}
		cout << count[9] << endl;
	}
	return 0;
}