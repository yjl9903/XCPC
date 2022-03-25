#include <cstdio>
#include <cstring>
#define is(x) x>=1&&x<=8
using namespace std;
char map[10][10] = { '\0' };
char f(char x)
{
	if (x == 'W')
		return 'B';
	else
		return 'W';
}
int isPlace(int tot, int x, int y, int t)//tot代表当前回合玩家,xy为目标点位
{
	if (map[x][y] != '-')
		return 0;

	int flag[10] = { 0 };
	char oth = f(tot);//表示对手

	flag[0] = (map[x][y + 1] == oth) && y + 1 <= 8;
	flag[1] = (map[x][y - 1] == oth) && y - 1 >= 1;
	flag[2] = (map[x + 1][y] == oth) && x + 1 <= 8;
	flag[3] = (map[x - 1][y] == oth) && x - 1 >= 1;
	flag[4] = (map[x - 1][y + 1] == oth) && x - 1 >= 1 && y + 1 <= 8;
	flag[5] = (map[x + 1][y + 1] == oth) && x + 1 <= 8 && y + 1 <= 8;
	flag[6] = (map[x + 1][y - 1] == oth) && x + 1 <= 8 && y - 1 >= 1;
	flag[7] = (map[x - 1][y - 1] == oth) && x - 1 >= 1 && y - 1 >= 1;

	for (int i = 2; i <= 7; i++)
	{
		if (flag[0] == 1 && is(y + i))
			if (map[x][y + i] == tot)
				flag[0] = 2;
			else if (map[x][y + i] == '-')
				flag[0] = 0;

		if (flag[1] == 1 && is(y - i))
			if (map[x][y - i] == tot)
				flag[1] = 2;
			else if (map[x][y - i] == '-')
				flag[1] = 0;

		if (flag[2] == 1 && is(x + i))
			if (map[x + i][y] == tot)
				flag[2] = 2;
			else if (map[x + i][y] == '-')
				flag[2] = 0;

		if (flag[3] == 1 && is(x - i))
			if (map[x - i][y] == tot)
				flag[3] = 2;
			else if (map[x - i][y] == '-')
				flag[3] = 0;

		if (flag[4] == 1 && is(x - i) && is(y + i))
			if (map[x - i][y + i] == tot)
				flag[4] = 2;
			else if (map[x - i][y + i] == '-')
				flag[4] = 0;

		if (flag[5] == 1 && is(x + i) && is(y + i))
			if (map[x + i][y + i] == tot)
				flag[5] = 2;
			else if (map[x + i][y + i] == '-')
				flag[5] = 0;

		if (flag[6] == 1 && is(x + i) && is(y - i))
			if (map[x + i][y - i] == tot)
				flag[6] = 2;
			else if (map[x + i][y - i] == '-')
				flag[6] = 0;

		if (flag[7] == 1 && is(x - i) && is(y - i))
			if (map[x - i][y - i] == tot)
				flag[7] = 2;
			else if (map[x - i][y - i] == '-')
				flag[7] = 0;

	}
	if (t)
	{
		for (int i = 1; i <= 7; i++)
		{
			if (flag[0] == 2)
				if (map[x][y + i] == oth)
					map[x][y + i] = tot;
				else
					flag[0] = 3;

			if (flag[1] == 2)
				if (map[x][y - i] == oth)
					map[x][y - i] = tot;
				else
					flag[1] = 3;

			if (flag[2] == 2)
				if (map[x + i][y] == oth)
					map[x + i][y] = tot;
				else
					flag[2] = 3;

			if (flag[3] == 2)
				if (map[x - i][y] == oth)
					map[x - i][y] = tot;
				else
					flag[3] = 3;

			if (flag[4] == 2)
				if (map[x - i][y + i] == oth)
					map[x - i][y + i] = tot;
				else
					flag[4] = 3;

			if (flag[5] == 2)
				if (map[x + i][y + i] == oth)
					map[x + i][y + i] = tot;
				else
					flag[5] = 3;

			if (flag[6] == 2)
				if (map[x + i][y - i] == oth)
					map[x + i][y - i] = tot;
				else
					flag[6] = 3;

			if (flag[7] == 2)
				if (map[x - i][y - i] == oth)
					map[x - i][y - i] = tot;
				else
					flag[7] = 3;
		}
	}
	for (int i = 0; i < 8; i++)
		if (flag[i] >= 2)
		{
			return 1;

		}
	return 0;
}
int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T, kase = 0;
	scanf("%d", &T);
	while (T--)
	{
		memset(map, '\0', sizeof map);
		char tot, cmd[5];
		for (int i = 1; i <= 8; i++)
		{
			getchar();
			for (int j = 1; j <= 8; j++)
				scanf("%c", &map[i][j]);

		}
		getchar();
		scanf("%c", &tot);

		if (kase++)
			printf("\n");

		while (scanf("%s", cmd) && cmd[0] != 'Q')
		{
			if (cmd[0] == 'L')
			{
				int flag = 0;
				for (int i = 1; i <= 8; i++)
					for (int j = 1; j <= 8; j++)
						if (isPlace(tot, i, j, 0))
						{
							if (flag++)
								printf(" ");
							printf("(%d,%d)", i, j);
						}
				if (!flag)
					printf("No legal move.");
				printf("\n");
			}
			else
			{
				int x = cmd[1] - '0', y = cmd[2] - '0';
				if (!isPlace(tot, x, y, 1))
				{
					tot = f(tot);
					isPlace(tot, x, y, 1);
				}
				map[x][y] = tot;
				tot = f(tot);
				int s1 = 0, s2 = 0;
				for (int i = 1; i <= 8; i++)
					for (int j = 1; j <= 8; j++)
						if (map[i][j] == 'B')
							s1++;
						else if (map[i][j] == 'W')
							s2++;
				printf("Black - %2d White - %2d\n", s1, s2);
			}
		}
		for (int i = 1; i <= 8; i++)
			printf("%s\n", map[i] + 1);
	}
	return 0;
}