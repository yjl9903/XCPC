#include <iostream>
#include <cstring>
using namespace std;
char result[3][20] = { "You lose.","You win.","You chickened out." };

int find(char x, char ans[], int len, int &cnt)
{
	int flag = 0;
	for (int i = 0; i < len; i++)
		if (ans[i] == x)
			flag = 1, ans[i] = 0, cnt--;
	return flag;
}
int main()
{
	int kase;
	char ans[100], gus[100];
	while (cin >> kase >> ans >> gus && kase > 0)
	{
		int flag = 2, wa = 0, rnd = 0, len = strlen(gus), len2 = strlen(ans), cnt = len2;
		for (; rnd < len; rnd++)
		{
			int x = find(gus[rnd], ans, len2, cnt);
			if (!cnt)
			{
				flag = 1;
				break;
			}
			if (!x)
				wa++;
			if (wa == 7)
			{
				flag = 0;
				break;
			}
		}
		cout << "Round " << kase << endl << result[flag] << endl;
	}
	return 0;
}