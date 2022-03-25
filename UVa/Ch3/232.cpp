#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#pragma warning(disable:4996)
//----------- A C -------------
//敲开心，用时：1h！！！
using namespace std;
char map[11][11];
int num[10][10];
char across[101][11];
int an[100];
char down[101][11];
int bn[100];
int getRes(char x[][11], int xn[100], int i, int j, int& acr, int& now);
int main()
{
	int kase = 1;
	while (true)
	{
		int row, col;
		cin >> row;
		if (row == 0)
			break;
		cin >> col;

		for (int i = 0; i < row; i++)
		{
			int j;
			for (j = 0; j < col; j++)
			{
				cin >> map[i][j];
			}
			map[i][j] = 0;
		}
		memset(map[row], 0, sizeof(map[row]));

		int order = 1;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				if (map[i][j] != '*')
					if (i == 0 || j == 0)
						num[i][j] = order++;
					else if (map[i - 1][j] == '*' || map[i][j - 1] == '*')
						num[i][j] = order++;
					else
						num[i][j] = 0;
			}
		int acr = 0, dow = 0, now = 0;
		for (int i = 0; i < row; i++)
		{
			now = 0;
			for (int j = 0; j < col; j++)
			{
				acr = getRes(across, an, i, j, acr, now);
			}
			if (now)
			{
				across[acr][now] = '\0';
				acr++;
			}
		}

		for (int j = 0; j < col; j++)
		{
			now = 0;
			for (int i = 0; i < row; i++)
			{
				dow = getRes(down, bn, i, j, dow, now);
			}
			if (now)
			{
				down[dow][now] = '\0';
				dow++;
			}
		}

		for (int i = 0; i < dow - 1; i++)
		{
			for (int j = i + 1; j < dow; j++)
			{
				if (bn[j] < bn[i])
				{
					int t = bn[j];
					bn[j] = bn[i];
					bn[i] = t;
					char xt[11];
					strcpy(xt, down[i]);
					strcpy(down[i], down[j]);
					strcpy(down[j], xt);
				}
			}
		}

		if (kase > 1)
			cout << endl;
		cout << "puzzle #" << kase++ << ':' << endl;
		cout << "Across" << endl;
		for (int i = 0; i < acr; i++)
		{
			cout << setw(3) << an[i] << '.' << across[i] << endl;
		}
		cout << "Down" << endl;
		for (int i = 0; i < dow; i++)
		{
			cout << setw(3) << bn[i] << '.' << down[i] << endl;
		}
	}
	return 0;
}
int getRes(char x[][11], int xn[100], int i, int j, int& acr, int& now)
{
	if (map[i][j] == '*')
	{
		if (now)
		{
			x[acr][now] = '\0';
			acr++;
		}
		now = 0;
	}
	else
	{
		if (!now)
		{
			x[acr][now++] = map[i][j];
			xn[acr] = num[i][j];
		}
		else
		{
			x[acr][now++] = map[i][j];
		}
	}
	return acr;
}