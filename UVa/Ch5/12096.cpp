#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <iterator>
#include <algorithm>
using namespace std;
map<set<int>, int> ID;
vector<set<int>> getSet;

int getID(set<int> x)
{
	if (ID.count(x))
		return ID[x];
	getSet.push_back(x);
	return ID[x] = getSet.size() - 1;
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		stack<int> s;
		int n;
		cin >> n;
		while (n--)
		{
			char cmd[10];
			cin >> cmd;
			if (cmd[0] == 'P')
				s.push(getID(set<int>()));
			else if (cmd[0] == 'D')
				s.push(s.top());
			else
			{
				set<int> x1 = getSet[s.top()];
				s.pop();
				set<int> x2 = getSet[s.top()];
				s.pop();
				set<int> x;
				if (cmd[0] == 'U')
					set_union(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(x,x.begin()));
				else if (cmd[0] == 'I')
					set_intersection(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(x, x.begin()));
				else if (cmd[0] == 'A')
				{
					x = x2;
					x.insert(getID(x1));
				}
				s.push(getID(x));
			}
			cout << getSet[s.top()].size() << endl;
		}
		cout << "***" << endl;
	}
	return 0;
}
