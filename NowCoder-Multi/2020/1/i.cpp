#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

namespace Matching
{
	const int maxn=511;
	int n,m;
	vector<int> con[maxn];
	int mt[maxn];
	void init(int N)
	{
		n=N;m=0;
		for(int i=1;i<=n;i++)con[i].clear();
		memset(mt,0,sizeof(mt));
	}
	void adde(int x,int y)
	{
		con[x].push_back(y);
		con[y].push_back(x);
	}
	int q[maxn],qn;
	int f[maxn],pre[maxn],mk[maxn];
	pair<int,int> cr[maxn];
	int gf(int x){return f[x]==x?x:f[x]=gf(f[x]);}
	void match(int x,int y){mt[x]=y;mt[y]=x;}
	void flip(int x,int y)
	{
		if(x==y)return;
		if(mk[y]==0)
		{
			flip(x,pre[pre[y]]);
			match(pre[y],pre[pre[y]]);
		}
		else
		{	
			flip(mt[y],cr[y].first);
			flip(x,cr[y].second);
			match(cr[y].first,cr[y].second);
		}
	}
	int tmp[maxn],ti;
	int getlca(int x,int y)
	{
		for(ti++,x=gf(x),y=gf(y);;x=gf(pre[x]),y=gf(pre[y]))
		{
			if(x&&tmp[x]==ti)return x;
			tmp[x]=ti;
			if(y&&tmp[y]==ti)return y;
			tmp[y]=ti;
		}
	}
	void blossom(int x,int p,pair<int,int> c)
	{
		for(x=gf(x);x!=p;x=gf(pre[x]))
		{
			f[x]=p;
			if(mk[x]==1)cr[x]=c,q[qn++]=x;
		}
	}
	bool bfs(int S)
	{
		for(int i=1;i<=n;i++)
		{
			mk[i]=-1;
			f[i]=i;
			pre[i]=0;
		}
		qn=0;
		q[qn++]=S;
		mk[S]=0;
		for(int i=0;i<qn;i++)
		{
			int x=q[i];
			for(int j=0;j<con[x].size();j++)
			{
				int u=con[x][j];
				if(gf(u)==gf(x))continue;
				if(mk[u]==-1)
				{
					if(!mt[u])
					{
						flip(S,x);
						match(x,u);
						return true;
					}
					else
					{
						int v=mt[u];
						pre[u]=x;pre[v]=u;
						mk[u]=1;mk[v]=0;
						q[qn++]=v;
					}
				}
				else
				{
					if(mk[gf(u)]==0)
					{
						int p=getlca(x,u);
						blossom(x,p,PII{x,u});
						blossom(u,p,PII{u,x});
					}
				}
			}
		}
		return false;
	}
	int solve()
	{
		for(int i=1;i<=n;i++)mt[i]=0;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(mt[i])continue;
			ans+=bfs(i);
		}
		return ans;
	}
};

int n, m, d[maxn];

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    map<int,int> fi, se;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", d + i);
      if (d[i] == 1) {
        fi[i] = ++cnt;
        se[i] = cnt;
      } else if (d[i] == 2) {
        fi[i] = ++cnt;
        se[i] = ++cnt;
      }
    }
    Matching::init(cnt);
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      Matching::adde(fi[u], fi[v]);
      Matching::adde(se[u], se[v]);
    }
    int ans = Matching::solve();
    cout << ans << endl;
  }
  return 0;
}