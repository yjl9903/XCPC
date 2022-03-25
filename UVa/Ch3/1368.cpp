#include <iostream>
#include <cstring>
using namespace std;
struct dna
{
	int A = 0, T = 0, G = 0, C = 0;
}s[2000];
char res[2000];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		memset(s, 0, sizeof(s));
		int m, n, sum = 0;
		char x;
		cin >> m >> n;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> x;
				switch (x)
				{
				case 'A':
					s[j].A++;
					break;
				case 'T':
					s[j].T++;
					break;
				case 'G':
					s[j].G++;
					break;
				case 'C':
					s[j].C++;
					break;
				}
			}
		}
		int i;
		for (i = 0; i < n; i++)
		{
			if (s[i].A >= s[i].T && s[i].A >= s[i].G && s[i].A >= s[i].C)
			{
				res[i] = 'A';
				sum += s[i].T + s[i].G + s[i].C;
			}
			else if (s[i].C >= s[i].A && s[i].C >= s[i].G && s[i].C >= s[i].T)
			{
				res[i] = 'C';
				sum += s[i].A + s[i].G + s[i].T;
			}
			else if (s[i].G >= s[i].A && s[i].G >= s[i].T && s[i].G >= s[i].C)
			{
				res[i] = 'G';
				sum += s[i].A + s[i].T + s[i].C;
			}
			else if (s[i].T >= s[i].A && s[i].T >= s[i].G && s[i].T >= s[i].C)
			{
				res[i] = 'T';
				sum += s[i].A + s[i].G + s[i].C;
			}		
		}
		res[i] = '\0';
		cout << res << endl << sum << endl;
	}
	return 0;
}