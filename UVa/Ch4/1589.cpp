#include <iostream>
#include <cstring>
using namespace std;
int N, bx, by;
int map[20][20] = { 0 };
int chess[20][20] = { 0 };

void cAtk(int x, int y)
{
	int flag = 0;
	for (int i = x + 1; i < 11; i++)
	{
		if (chess[i][y] < 2 && flag)
			map[i][y] = 1;
		if (chess[i][y] > 1 && flag)
		{
			map[i][y] = 1; break;
		}
		else if (chess[i][y] > 1)
			flag = 1;
	}
	flag = 0;
	for (int i = x - 1; i > 0; i--)
	{
		if (chess[i][y] < 2 && flag)
			map[i][y] = 1;
		if (chess[i][y] > 1 && flag)
		{
			map[i][y] = 1; break;
		}
		else if (chess[i][y] > 1)
			flag = 1;
	}
	flag = 0;
	for (int i = y + 1; i < 10; i++)
	{
		if (chess[x][i] < 2 && flag)
			map[x][i] = 1;
		if (chess[x][i] > 1 && flag)
		{
			map[x][i] = 1; break;
		}
		else if (chess[x][i] > 1)
			flag = 1;
	}
	flag = 0;
	for (int i = y - 1; i > 0; i--)
	{
		if (chess[x][i] < 2 && flag)
			map[x][i] = 1;
		if (chess[x][i] > 1 && flag)
		{
			map[x][i] = 1; break;
		}
		else if (chess[x][i] > 1)
			flag = 1;
	}
}
void rAtk(int x, int y)
{
	for (int i = x + 1; i <= 10; i++)
		if (chess[i][y] > 1)
		{
			map[i][y] = 1; break;
		}
		else
			map[i][y] = 1;
	for (int i = x - 1; i > 0; i--)
		if (chess[i][y] > 1)
		{
			map[i][y] = 1; break;
		}
		else
			map[i][y] = 1;

	for (int i = y + 1; i <= 9; i++)
		if (chess[x][i] > 1)
		{
			map[x][i] = 1; break;
		}
		else
			map[x][i] = 1;

	for (int i = y - 1; i > 0; i--)
		if (chess[x][i] > 1)
		{
			map[x][i] = 1; break;
		}
		else
			map[x][i] = 1;

}
void hAtk(int x, int y)
{
	if (!chess[x][y + 1])
	{
		if (x - 1 > 0 && y + 2 < 10)
			map[x - 1][y + 2] = 1;
		if (x + 1 < 11 && y + 2 < 10)
			map[x + 1][y + 2] = 1;
	}
	if (!chess[x][y - 1])
	{
		if (x - 1 > 0 && y - 2 > 0)
			map[x - 1][y - 2] = 1;
		if (x + 1 < 11 && y - 2 > 0)
			map[x + 1][y - 2] = 1;
	}
	if (!chess[x + 1][y])
	{
		if (x + 2 < 11 && y - 1 > 0)
			map[x + 2][y - 1] = 1;
		if (x + 2 < 11 && y + 1 < 10)
			map[x + 2][y + 1] = 1;
	}
	if (!chess[x - 1][y])
	{
		if (x - 2 > 0 && y - 1 > 0)
			map[x - 2][y - 1] = 1;
		if (x - 2 > 0 && y + 1 < 10)
			map[x - 2][y + 1] = 1;
	}
}
int main()
{
	while (cin >> N >> bx >> by && N)
	{
		memset(map, 0, sizeof map);
		memset(chess, 0, sizeof chess);
		chess[bx][by] = 1;
		int rx, ry, cnt[10] = { 0 }, xx[10][10] = { 0 }, yy[10][10] = { 0 };
		while (N--)
		{
			int x, y;
			char t;
			cin >> t >> x >> y;
			if (t == 'G')
			{
				chess[x][y] = 2;
				rx = x;
				ry = y;
			}
			else if (t == 'R')
			{
				chess[x][y] = 3;
				xx[0][cnt[0]] = x;
				yy[0][cnt[0]++] = y;

			}
			else if (t == 'H')
			{
				chess[x][y] = 4;
				xx[1][cnt[1]] = x;
				yy[1][cnt[1]++] = y;

			}
			else
			{
				chess[x][y] = 5;
				xx[2][cnt[2]] = x;
				yy[2][cnt[2]++] = y;

			}
		}
		for (int i = 0; i < cnt[0]; i++)
			rAtk(xx[0][i], yy[0][i]);
		for (int i = 0; i < cnt[1]; i++)
			hAtk(xx[1][i], yy[1][i]);
		for (int i = 0; i < cnt[2]; i++)
			cAtk(xx[2][i], yy[2][i]);

		int flag = 1;
		for (int i = rx - 1; i > 0; i--)
			if (chess[i][ry] > 2)
				flag = 0;
		if (flag)
		{
			if (chess[1][ry] == 1 || chess[2][ry] == 1 || chess[3][ry] == 1)
			{
				cout << "NO" << endl;
				continue;
			}
		}
		rAtk(rx, ry);
		flag = 1;
		if (bx - 1 > 0 && !map[bx - 1][by])
			flag = 0;
		if (bx + 1 < 4 && !map[bx + 1][by])
			flag = 0;
		if (by - 1 > 3 && !map[bx][by - 1])
			flag = 0;
		if (by + 1 < 7 && !map[bx][by + 1])
			flag = 0;
		cout << (flag ? "YES" : "NO") << endl;

	}
	return 0;
}