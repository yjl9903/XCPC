#include <bits/stdc++.h>
using namespace std;
int n,m,k,x,y;
string S,T;
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&k,&x,&y);
	cin>>S>>T;
	int tmpx=x,tmpy=y;
	for(int i=0;i<k;i++)
	{
		if(S[i]=='U') tmpx--;
		if(tmpx<1)
		{
			printf("NO");
			return 0;
		}
		if(T[i]=='D'&&tmpx!=n) tmpx++;
	}
	tmpx=x;
	for(int i=0;i<k;i++)
	{
		if(S[i]=='D') tmpx++;
		if(tmpx>n)
		{
			printf("NO");
			return 0;
		}
		if(T[i]=='U'&&tmpx!=1) tmpx--;
	}
	tmpx=x;
	for(int i=0;i<k;i++)
	{
		if(S[i]=='L') tmpy--;
		if(tmpy<1)
		{
			printf("NO");
			return 0;
		}
		if(T[i]=='R'&&tmpy!=m) tmpy++;
	}
	tmpy=y;
	for(int i=0;i<k;i++)
	{
		if(S[i]=='R') tmpy++;
		if(tmpy>m)
		{
			printf("NO");
			return 0;
		}
		if(T[i]=='L'&&tmpy!=1) tmpy--;
	}
	printf("YES");
	return 0;
}