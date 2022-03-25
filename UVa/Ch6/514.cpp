#include <iostream>
#include <stack>
using namespace std;
stack<int> A, C;
int res[1005] = { 0 };
void clear(stack<int> &x)
{
	while (!x.empty())
		x.pop();
}
bool solve(int N)
{
	int tot = 1;
	while (!A.empty())
	{
		if (!C.empty() && C.top() == res[tot])
		{
			C.pop();
			tot++;
		}
		else
		{
			C.push(A.top());
			A.pop();
		}
	}
	while (!C.empty())
	{
		if (C.top() != res[tot])
			return false;
		C.pop();
		tot++;
	}
	return true;
}
int main()
{
	int N;
	while (cin >> N && N)
	{
		while (cin >> res[1] && res[1])
		{
			for (int i = 2; i <= N; i++)
				cin >> res[i];
			clear(A); clear(C);
			for (int i = N; i > 0; i--)
				A.push(i);
			cout << (solve(N) ? "Yes" :"No") << endl;
		}
		cout << endl;
	}
	return 0;
}