#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
map<string, int> ID;
vector<string> getStr;
//int table[10010][15];
vector<int> table[10010];
int getID(string& x)
{
	if (ID.count(x))
		return ID[x];
	getStr.push_back(x);
	return ID[x] = getStr.size() - 1;
}
struct point { 
	int x; int y; 
	point(int x1, int x2) :x(x1), y(x2) {};
};
bool operator<(const point& x1, const point& x2)
{
	return x1.x < x2.x || x1.x == x2.x && x1.y < x2.y;
}
map<point, int> check;
void read(int n)
{
	string str;
	char ch = getchar();
	for(int i = 0; i < n; i++)
		while (true)
		{
			ch = getchar();
			if (ch == '\n' || ch == '\r')
			{
				if (!str.empty())
					table[i].push_back(getID(str));
				str.clear();
				break;
			}
			if (ch == ',')
			{
				table[i].push_back(getID(str));
				str.clear();
			}
			else
				str += ch;
		}
}
int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int n, m;
	while (cin >> n >> m)
	{
		/*for (int i = 0; i < n; i++)
		{
			cin.get();
			for (int j = 0; j < m - 1; j++)
			{
				string str;
				getline(cin, str, ',');
				table[i][j] = getID(str);
			}
			string str;
			cin >> str;
			table[i][m - 1] = getID(str);
		}*/
		read(n);
		int flag = 1;
		for (int c1 = 0; c1 < m; c1++)
			for (int c2 = c1 + 1; c2 < m; c2++)
			{
				if (flag)
				{
					check.clear();
					for (int i = 0; i < n; i++)
					{
						point x(table[i][c1], table[i][c2]);
						if (check.count(x))
						{
							flag = 0;
							cout << "NO" << endl << check[x] + 1 << ' ' << i + 1 << endl << c1 + 1 << ' ' << c2 + 1 << endl;
							break;
						}
						check[x] = i;
					}
				}
			}
		if (flag)
			cout << "YES" << endl;
		memset(table, 0, sizeof table);
		ID.clear();
		getStr.clear();
	}
	return 0;
}