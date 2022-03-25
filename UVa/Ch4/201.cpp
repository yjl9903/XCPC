#include <iostream>
#include <cstring>
using namespace std;
int h[20][20] = { 0 }, v[20][20] = { 0 }, res[20] = { 0 };

void show(int size)
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size - 1; j++)
			cout << h[i][j] << ' ';
		cout << endl;
	}
	for (int i = 1; i <= size - 1; i++)
	{
		for (int j = 1; j <= size; j++)
			cout << v[i][j] << ' ';
		cout << endl;
	}

}
int main()
{
	//freopen("in.txt", "r", stdin);
	int kase = 0, size, T;
	while (cin >> size >> T)
	{
		memset(h, 0, sizeof h);
		memset(v, 0, sizeof v);
		memset(res, 0, sizeof res);
		while (T--)
		{
			char s;
			int x, y;
			cin >> s >> x >> y;
			if (s == 'H')
				h[x][y] = 1;
			else
				v[y][x] = 1;
		}
		int flag = 1;//标记是否完全无解
		for (int s = 1; s <= size; s++)
		{
			int cnt = 0;
			for (int i = 1; i <= size - s; i++)
				for (int j = 1; j <= size - s; j++)
				{
					int mark = 1;//标记是否缺少边
					for (int x = j; x <= j + s - 1; x++)
						if (!h[i][x] || !h[i + s][x])
							mark = 0;

					for (int x = i; x <= i + s - 1; x++)
						if (!v[x][j] || !v[x][j + s])
							mark = 0;
					if (mark)
						cnt++;
				}
			res[s] = cnt;
			if (cnt)
				flag = 0;
		}
		if(kase)
			cout << endl << "**********************************" << endl << endl;
		cout << "Problem #" << ++kase << endl << endl;
		if (flag)
			cout << "No completed squares can be found." << endl;
		for (int i = 1; i <= size; i++)
			if (res[i])
				cout << res[i] << " square (s) of size " << i << endl;
		
		//show(size);
	}
	return 0;
}