#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 100
using namespace std;
double molar[4] = { 12.01,1.008,16.00,14.01 };
//
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		char s[maxn];
		cin >> s;
		int len = strlen(s), flag = 0, now = 0, t = 0;
		double sum = 0;
		for (int i = 0; i < len; i++)
		{
			switch (s[i])
			{
			case 'C':
				sum += now * molar[t];
				now = 0;
				t = 0;
				break;
			case 'H':
				sum += now * molar[t];
				now = 0;
				t = 1;
				break;
			case 'O':
				sum += now * molar[t];
				now = 0;
				t = 2;
				break;
			case 'N':
				sum += now * molar[t];
				now = 0;
				t = 3;
				break;
			default:
				now = 10 * now + s[i]-'0';
				break;
			}
			if (s[i] > '9' && (s[i + 1] > '9' || s[i + 1] < '0'))
				sum += molar[t];
		}
		sum += now * molar[t];
		printf("%.3f\n", sum);
	}
	return 0;
}