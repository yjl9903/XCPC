#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

const int MAXN=110;
vector<int> G[MAXN];
int mp[MAXN][MAXN];
int n,m,s;
int T;
int ans;

void dfs(int u,int * tmp, int size)
{
    if (size==s)
    {
        ans++;
        return;
    }
    bool f;
    for(int i=0; i<G[u].size(); i++)//可能加入团的点
    {
        int v=G[u][i];
        f=true;
        for(int j=1; j<=size; j++)//遍历团中所有点，判断是否与将要加入的点相连
        {
            if (!mp[v][tmp[j]])
            {
                f=false;
                break;
            }
        }
        if (f)//这个点可以加入团，加入并继续深搜
        {
            size++;
            tmp[size]=v;
            dfs(v,tmp,size);
            tmp[size]=0;
            size--;
        }
    }
}

int main()
{
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d",&n,&m,&s);
        for(int i=1; i<=n; i++) G[i].clear();
        memset(mp,0,sizeof(mp));
        ans=0;
        while(m--)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            G[u].push_back(v);
            mp[u][v]=mp[v][u]=1;
        }
        for(int i=1; i<=n; i++)
        {
            int size=1;//团的规模
            int tmp[MAXN];//tmp集合表示这个团中有哪些点 
            tmp[1]=i;
            dfs(i,tmp,size);
        }
        printf("%d\n",ans);
    }
    return 0;
}