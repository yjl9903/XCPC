#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
struct point { int x, y; };
bool cmp(const point &x1,const point &x2)
{
	return x1.x < x2.x && x1.y < x2.y;
}
int main()
{
	point b[10];
	while (cin >> b[0].x >> b[0].y)
	{

		if (b[0].x > b[0].y)		swap(b[0].x, b[0].y);
		for (int i = 1; i < 6; i++)
		{
			cin >> b[i].x >> b[i].y;
			if (b[i].x > b[i].y)
				swap(b[i].x, b[i].y);
		}
		sort(b, b + 6, cmp);
		//cout << b << b + 6;
		int flag = 1;
		for (int i = 0; i < 6; i += 2)
			if (b[i].x != b[i + 1].x || b[i].y != b[i + 1].y)
				flag = 0;
		if (b[0].x != b[2].x || b[0].y != b[4].x || b[2].y != b[4].y)
			flag = 0;
		cout << (flag ? "POSSIBLE" : "IMPOSSIBLE") << endl;
	}
	return 0;
}