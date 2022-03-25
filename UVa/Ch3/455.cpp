#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		char s[100], a[100];
		cin >> s;
		int t = 1, len = strlen(s);
		
		for (t = 1; t < len; t++)
		{
			if (!(len % t))
			{
				int flag = 1;
				for (int i = t; i < len; i++)
				{
					if (s[i%t] != s[i])
						flag = 0;
				}
				if (flag)
					break;
			}
		}

		cout << t << endl;
		if (T)
			cout << endl;
	}
	return 0;
}