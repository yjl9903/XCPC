#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<stack>
#include<string>
#include<set>
using namespace std;
#define M 1500010
#define P 4294967296
long long n, x, k, w[M], e[M];
string s[M];
void a()
{
	x++;
}
int f(long long t)
{
	int i, j;
	i = t+1;
	for (j = 1; j <= w[t]; j++)
	{
		if (e[t] == -1)
		{
			int t1, t2;
			t1 = x;
			for (i = t + 1; s[i][0] != 'e'; i++)
			{
				if (s[i][0] == 'a')
				{
					a();
				}
				if (s[i][0] == 'f')
				{
					i = f(i);
				}
			}
			t2 = x;
			e[t] = t2 - t1;
		}
		else
		{
			x = x + e[t];
		}
		if (x<0 || x>=P)
		{
			break;
		}
	}
	return i;
}
int main()
{
	cin >> n;
	x = 0;
	k = 1;
	memset(e, -1, sizeof(e));
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
		if (s[i][0] == 'f')
		{
			cin >> w[i];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (s[i][0] == 'f')
		{
			i = f(i);
		}
		if (s[i][0] == 'a')
		{
			a();
		}
		if (x<0 || x>=P)
		{
			break;
		}
	}
	if (x >= 0 && x < P)
	{
		cout << x;
	}
	else if (x < 0 || x >= P)
	{
		cout << "OVERFLOW!!!";
	}
}