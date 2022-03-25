#include <iostream>
#include <cstring>
#define maxn 1000
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		char s[maxn];
		cin >> s;
		int len = strlen(s), sum = 0, point = 0;
		for (int i = 0; i < len; i++)
		{
			if (s[i] == 'O')
			{
				sum += ++point;
			}
			else
			{
				point = 0;
			}
		}
		cout << sum << endl;
	}
	return 0;
}