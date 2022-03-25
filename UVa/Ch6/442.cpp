#include <iostream>
#include <stack>
#include <string>
#include <utility>
#define p pair<int, int>
using namespace std;
p x[30];
long long solve(string& exp)
{
	stack<p> cal;
	long long tot = 0, sum = 0;
	if (exp.length() == 1)
		return 0;
	while (tot < exp.length())
	{
		if (exp[tot] == ')')
		{
			p x2 = cal.top(); cal.pop();
			p x1 = cal.top(); cal.pop();
			if (x1.second != x2.first)
				return -1;
			else
				sum += x1.first * x1.second * x2.second;
			cal.push(make_pair(x1.first, x2.second));
		}
		else if (exp[tot] != '(')
			cal.push(x[exp[tot] - 'A']);
		tot++;
	}
	return sum;
}
int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char xx;
		int r, c;
		cin >> xx >> r >> c;
		x[xx - 'A'] = make_pair(r, c);
	}
	string exp;
	while (cin >> exp) 
	{
		long long res = solve(exp);
		if (res != -1)
			cout << res;
		else
			cout << "error";
		cout << endl;
	}
	return 0;
}