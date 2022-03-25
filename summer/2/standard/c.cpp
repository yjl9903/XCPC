#include<bits/stdc++.h>
#define F(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int AC_N=10000*51,tyn=26;
struct AC_automation{
    int tr[AC_N][tyn],cnt[AC_N],Q[AC_N],fail[AC_N],fa[AC_N],tot;
    inline int getid(char x){return x-'a';}
    void nw(){cnt[++tot]=0,fail[tot]=0;memset(tr[tot],0,sizeof(tr[tot]));}
    void init(){tot=-1,fail[0]=-1,nw();}
    void insert(char *s,int x=0){
        for(int i=0,w;s[i];x=tr[x][w],i++)
            if(!tr[x][w=getid(s[i])])nw(),tr[x][w]=tot,fa[tot]=x;
        cnt[x]++;//串尾标记 
    }
    void build(int head=1,int tail=0){
        for(int i=0;i<tyn;i++)if(tr[0][i])Q[++tail]=tr[0][i];
        while(head<=tail)for(int x=Q[head++],i=0;i<tyn;i++)
            if(tr[x][i])fail[tr[x][i]]=tr[fail[x]][i],Q[++tail]=tr[x][i];
            else tr[x][i]=tr[fail[x]][i];
    }
    int sum[AC_N];//以i节点为后缀的前缀个数
    vector<int>g[AC_N];
    
    void dfs(int x)
    {
        sum[x]=1;
        for(auto &it:g[x])
            dfs(it),sum[x]+=sum[it];
    }
    void solve()
    {
        F(i,0,tot)g[i].clear();
        F(i,1,tot)g[fail[i]].push_back(i);
        dfs(0);
        long long tmp=0;
        F(i,1,tot)if(fail[i])
        {
            int p=fail[i],q=i;
            while(p)p=fa[p],q=fa[q];
            tmp+=sum[q]-1;
        }
        printf("%lld\n",1ll*tot*tot-tmp);
    }
}AC;

int n;
char s[50];

int main()
{
    while(scanf("%d",&n),n)
    {
        AC.init();
        F(i,1,n)scanf("%s",s),AC.insert(s);
        AC.build(),AC.solve();
    }
    return 0;
}