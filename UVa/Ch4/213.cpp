#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char code[10][100] = { 0 };
char anw[1000] = { "\0" };

int read(int x)
{
	int s = 0, t;
	while (x--)
	{
		t = getchar();
		while (t == '\n' || t == '\r')
			t = getchar();
		s = 2 * s + t - '0';
	}
	return s;
}
int readcode()
{
	memset(code, 0, sizeof(code));
	memset(anw, '\0', sizeof(anw));
	code[1][0] = getchar();
	while (code[1][0] == '\n' || code[1][0] == '\r')
		code[1][0] = getchar();
	for (int i = 2, cnt = 0, col = 4; i <= 7; i++, col *= 2)
	{
		for (int j = 0; j < col - 1; j++, cnt++)
		{
			int ch = getchar();
			if (ch == EOF)
				return 0;
			if (ch == '\n' || ch == '\r')
				return 1;
			code[i][j] = ch;
		}
	}
	return 1;
}
int main()
{
	char head[100];
	while (readcode())
	{
		int clen;
		while (clen = read(3))
		{
			int end = (1 << clen) - 1, tot, cnt = 0;
			while (tot = read(clen), tot != end)
			{
				cout << code[clen][tot];
			}
		}
		cout << endl;
	}
	return 0;
}