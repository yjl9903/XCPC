#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
//char cmd[100] = { '\0' };
struct point { int r = 0; int c = 0; }sheet[60][60], sheet2[60][60];
int r, c;

void show()
{
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			cout << sheet[i][j].r << ' ' << sheet[i][j].c << '|';
		}
		cout << endl;
	}
}
void ex()
{
	int r1, r2, c1, c2;
	cin >> r1 >> c1 >> r2 >> c2;
	swap(sheet[r1][c1], sheet[r2][c2]);
}
void copy(int type, int x, int y)
{
	//show();
	if (type)
		for (int i = 1; i <= r; i++)
			sheet2[i][x] = sheet[i][y];
	else
		for (int i = 1; i <= c; i++)
			sheet2[x][i] = sheet[y][i];
}
void del(int type)//type为0对行操作，1对列操作
{
	//char obj[100] = { '\0' };
	//cin.getline(obj, 100);

	int T, cols[100] = { 0 }, cnt = 0;
	cin >> T;
	while (T--)
	{
		int x;
		cin >> x;
		cols[x] = 1;
	}
	if (type)
	{
		for (int j = 1; j <= c; j++)
			if (!cols[j])
				copy(type, ++cnt, j);
		c = cnt;
	}
	else
	{
		for (int i = 1; i <= r; i++)
			if (!cols[i])
				copy(type, ++cnt, i);
		r = cnt;
	}
	memcpy(sheet, sheet2, sizeof(sheet2));
	//cout << "OK" << endl;
}

void ist(int type)
{
	//char obj[100] = { '\0' };
	//cin.getline(obj, 100);

	int T, cols[100] = { 0 }, cnt = 0;
	cin >> T;
	while (T--)
	{
		int x;
		cin >> x;
		cols[x] = 1;
	}
	if (type)
	{
		for (int i = 1; i <= c; i++)
		{
			if (cols[i])
				copy(type, ++cnt, 0);
			copy(type, ++cnt, i);
		}
		c = cnt;
	}
	else
	{
		for (int i = 1; i <= r; i++)
		{
			if (cols[i])
				copy(type, ++cnt, 0);
			copy(type, ++cnt, i);
		}
		r = cnt;
	}
	memcpy(sheet, sheet2, sizeof(sheet2));
	//cout << "OK" << endl;
}

int main()
{
	int kase = 0;
	while (cin >> r >> c && r != 0 && c != 0)
	{
		int t;
		cin >> t;
		memset(sheet, 0, sizeof(sheet));
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++)
				sheet[i][j].r = i, sheet[i][j].c = j;

		//show();

		while (t--)
		{
			char cmd[5];
			cin >> cmd;
			if (cmd[0] == 'E')
				ex();
			else if (cmd[0] == 'D')
				if (cmd[1] == 'R')
					del(0);
				else
					del(1);
			else if (cmd[0] == 'I')
				if (cmd[1] == 'R')
					ist(0);
				else
					ist(1);
		}

		//show();
		if (kase)
			cout << endl;
		cout << "Spreadsheet #" << ++kase << endl;
		cin >> t;
		while (t--)
		{
			int dr, dc, flag = 1;
			cin >> dr >> dc;
			printf("Cell data in (%d,%d) ", dr, dc);
			for (int i = 1; i <= r; i++)
				for (int j = 1; j <= c; j++)
					if (dr == sheet[i][j].r && dc == sheet[i][j].c)
					{
						flag = 0;
						printf("moved to (%d,%d)", i, j);
					}
			if (flag)
				printf("GONE");
			cout << endl;
		}
	}
	return 0;
}