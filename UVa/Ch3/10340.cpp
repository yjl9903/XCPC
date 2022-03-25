#include <iostream>
#include <cstring>

using namespace std;

char s[100100], t[100100];
char f[2][5] = { "No","Yes" };
int main()
{
	while (cin >> s >> t)
	{
		int slen = strlen(s), tlen = strlen(t), flag = 0;
		for (int i = 0, j = 0; i < tlen; i++)
		{
			if (s[j] == t[i])
				j++;
			if (j == slen)
			{
				flag = 1;
				break;
			}
		}
		cout << f[flag] << endl;
	}
	return 0;
}