#include <iostream>
#include <cstring>
using namespace std;
int nxt[100005];
char txt[100005];
int main()
{
	while (cin >> txt + 1)
	{
		int i = 1, len =  strlen(txt + 1), last = 0, ans = 0;
		nxt[0] = 0;
		while (i <= len)
		{
			if (txt[i] == '[')
			{
				ans = 0;
			}
			else if (txt[i] == ']')
			{
				ans = last;
			}
			else
			{
				nxt[i] = nxt[ans];
				nxt[ans] = i;
				if (ans == last)
					last = i;
				ans = i;
			}
			i++;
		}
		for (int i = nxt[0]; i; i = nxt[i])
			cout << txt[i];
		cout << endl;
	}
	return 0;
}