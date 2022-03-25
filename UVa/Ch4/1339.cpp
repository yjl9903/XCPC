#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
char a[1000], b[1000];
char an[30], bn[30];

int main()
{
	while (cin >> a >> b)
	{
		memset(an, 0, sizeof(an));
		memset(bn, 0, sizeof(bn));
		int flag = 1;
		for (int i = 0; a[i] != '\0'; i++)
			an[a[i] - 'A']++;
		for (int i = 0; b[i] != '\0'; i++)
			bn[b[i] - 'A']++;

		sort(an, an + 26);
		sort(bn, bn + 26);
		for (int i = 0; i < 26; i++)
			if (an[i] != bn[i])
				flag = 0;

		cout << (flag ? "YES" : "NO") << endl;
	}

	return 0;
}