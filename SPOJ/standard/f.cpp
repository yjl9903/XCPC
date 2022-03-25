#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<cmath>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define inf 1000000000
#define pa pair<int,int>
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int ans;
int n,K,m,cnt;
int rt,sum,deep_mx;
int last[200005],siz[200005],f[200005],deep[200005],dis[200005];
bool color[200005],vis[200005];
vector<pair<int,int> >st;
int tmp[200005],mx[200005];
struct edge{
	int to,next,v;
}e[400005];
void insert(int u,int v,int w)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;
	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;e[cnt].v=w;
}
void getroot(int x,int fa)
{
	siz[x]=1;f[x]=0;
	for(int i=last[x];i;i=e[i].next)
		if(!vis[e[i].to]&&e[i].to!=fa)
		{
			getroot(e[i].to,x);
			f[x]=max(f[x],siz[e[i].to]);
			siz[x]+=siz[e[i].to];
		}
	f[x]=max(f[x],sum-siz[x]);
	if(f[x]<f[rt])rt=x;
}
void getdis(int x,int fa)
{
	deep_mx=max(deep_mx,deep[x]);
	for(int i=last[x];i;i=e[i].next)
		if(!vis[e[i].to]&&e[i].to!=fa)
		{
			deep[e[i].to]=deep[x]+color[e[i].to];
			dis[e[i].to]=dis[x]+e[i].v;
			getdis(e[i].to,x);
		}
}
void getmx(int x,int fa)
{
	tmp[deep[x]]=max(tmp[deep[x]],dis[x]);
	for(int i=last[x];i;i=e[i].next)
		if(!vis[e[i].to]&&e[i].to!=fa)
			getmx(e[i].to,x);
}
void solve(int x)
{
	vis[x]=1;st.clear();
	if(color[x])K--;
	for(int i=last[x];i;i=e[i].next)
		if(!vis[e[i].to])
		{
			deep_mx=0;
			deep[e[i].to]=color[e[i].to];
			dis[e[i].to]=e[i].v;
			getdis(e[i].to,x);
			st.push_back(make_pair(deep_mx,e[i].to));
		}
	sort(st.begin(),st.end());
	for(int i=0;i<st.size();i++)
	{
		getmx(st[i].second,x);
		int now=0;
		if(i!=0)
			for(int j=st[i].first;j>=0;j--)
			{
				while(now+j<K&&now<st[i-1].first)
					now++,mx[now]=max(mx[now],mx[now-1]);
				if(now+j<=K)ans=max(ans,mx[now]+tmp[j]);
			}
		if(i!=st.size()-1)
			for(int j=0;j<=st[i].first;j++)
				mx[j]=max(mx[j],tmp[j]),tmp[j]=0;
		else 
			for(int j=0;j<=st[i].first;j++)
			{
				if(j<=K)ans=max(ans,max(tmp[j],mx[j]));
				tmp[j]=mx[j]=0;
			}
	}
	if(color[x])K++;
	for(int i=last[x];i;i=e[i].next)
		if(!vis[e[i].to])
		{
			rt=0;sum=siz[e[i].to];
			getroot(e[i].to,x);
			solve(rt);
		}
}
int main()
{
	n=read();K=read();m=read();
	for(int i=1;i<=m;i++)
	{
		int x=read();
		color[x]=1;
	}
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read(),w=read();
		insert(u,v,w);
	}
	sum=n;f[0]=n;
	getroot(1,0);
	solve(rt);
	printf("%d\n",ans);
	return 0;
}