#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	int kase = 0, aaa = 0;
	while (true)
	{
		char map[5][5];
		cin.getline(map[0], 10);
		
		if (map[0][0] == 'Z')
			break;

		cin.getline(map[1], 10);
		cin.getline(map[2], 10);
		cin.getline(map[3], 10);
		cin.getline(map[4], 10);

		int x = 0, y = 0;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (map[i][j] == ' ')
				{
					y = i;
					x = j;
				}

		char a[100];
		int an = 0;
		while (cin >> a[an])
		{
			if (a[an] == '0')
				break;
			else
				an++;
		}
		cin.get();
		int i = -1, flag = 1;
		while (a[++i] != '0')
		{
			int nx = x, ny = y;
			switch (a[i])
			{
			case 'A':
				ny--;
				break;
			case 'B':
				ny++;
				break;
			case 'L':
				nx--;
				break;
			case 'R':
				nx++;
				break;
			}
			if (nx < 0 || nx > 4 || ny < 0 || ny > 4)
			{
				flag = 0;
				break;
			}
			else
			{
				char temp = map[y][x];
				map[y][x] = map[ny][nx];
				map[ny][nx] = temp;
				x = nx;
				y = ny;
			}
		}
		if (aaa)
			cout << endl;
		aaa = 1;
		cout << "Puzzle #" << ++kase << ":" << endl;
		if (flag)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cout << map[i][j] << ' ';
				}
				cout << map[i][4] << endl;
			}
		}
		else
		{
			cout << "This puzzle has no final configuration." << endl;
		}
	}
	return 0;
}