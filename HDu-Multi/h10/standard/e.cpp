#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
const int maxnd=8.1e7+10;
const int range=1e5;

int n,f[maxn],Ans[maxn],fa;
int totnd,root[maxn];
int lc[maxnd],rc[maxnd];
vector<int> d[maxn];

void build(int &x,int s,int t,int pos)
{
	if (!x) {x=++totnd; lc[x]=rc[x]=0;}
	if (s==t) return;
	int mid=(s+t)>>1;
	if (pos<=mid) build(lc[x],s,mid,pos);
	else build(rc[x],mid+1,t,pos);
}

int merge(int x,int y,int s,int t)
{
	if (!x||!y) return x^y;
	if (s==t) {Ans[fa]=max(Ans[fa],s); return x;}
	int mid=(s+t)>>1;
	lc[x]=merge(lc[x],lc[y],s,mid);
	rc[x]=merge(rc[x],rc[y],mid+1,t);
	return x;
}

int main()
{
	int i,j,x;
	for (i=1;i<=range;i++)
	for (j=1;i*j<=range;j++)
		d[i*j].push_back(i);

	scanf("%d",&n);
	for (i=1;i<=n;i++) Ans[i]=-1;
	for (i=2;i<=n;i++)
		scanf("%d",&f[i]);
		
	totnd=0;
	for (i=1;i<=n;i++)
	{
		scanf("%d",&x);
		root[i]=++totnd;
		lc[root[i]]=rc[root[i]]=0;
		for (j=0;j<(int)d[x].size();j++)
			build(root[i],1,range,d[x][j]);
	}
	for (i=n;i>=1;i--)
	{
		fa=f[i];
		root[fa]=merge(root[fa],root[i],1,range);
	}
	for (i=1;i<=n;i++)
		printf("%d\n",Ans[i]);
}

