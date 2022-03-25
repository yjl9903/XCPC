#include<bits/stdc++.h>
using namespace std;
const int M=2e5+5;
 
int n,ROOT,A[M];
struct Edge{int v,to;}E[M<<1];int Head[M],e_tot;
void Link(int u,int v){E[++e_tot]=(Edge){v,Head[u]},Head[u]=e_tot;}
 
int dep[M],Fa[M],son[M],siz[M],tp[M],dfn[M],post[M],Dfnc;
void dfs_Init(int u)
{
    siz[u]=1;dfn[u]=++Dfnc;
    for(int i=Head[u];i;i=E[i].to)
    {
        int v=E[i].v;if(v==Fa[u])continue;
        Fa[v]=u;dep[v]=dep[u]+1;
        dfs_Init(v);
        siz[u]+=siz[v];if(siz[v]>siz[son[u]])son[u]=v;
    }
    post[u]=Dfnc;
}
void re_dfs_Init(int u)
{
    for(int i=Head[u];i;i=E[i].to)
    {
        int v=E[i].v;if(v==Fa[u])continue;
        tp[v]=v==son[u]?tp[u]:v;
        re_dfs_Init(v);
    }
}
int LCA(int u,int v)
{
    while(tp[u]!=tp[v])
        if(dep[tp[u]]<dep[tp[v]])v=Fa[tp[v]];
        else u=Fa[tp[u]];
    return dep[u]<dep[v]?u:v;
}
bool In(int u,int v){return dfn[u]>=dfn[v] && dfn[u]<=post[v];}
 
int Vec[M<<1],tot;
Edge V[M<<1];int Vead[M],v_tot;
void Vink(int u,int v){V[++v_tot]=(Edge){v,Vead[u]},Vead[u]=v_tot;}
void clearv(){for(int i=1;i<=tot;i++)Vead[Vec[i]]=0;v_tot=0;}
int Va[M],Voot;
 
bool cmp(int x,int y){return dfn[x]<dfn[y];}
int Stk[M],top;
void Build_VT()
{
    sort(Vec+1,Vec+tot+1,cmp);
    for(int i=1,tmp=tot;i<tmp;i++)Vec[++tot]=LCA(Vec[i],Vec[i+1]);
    sort(Vec+1,Vec+tot+1,cmp);
    int tmp=0;
    for(int i=1;i<=tot;i++)if(i==1 || Vec[i]!=Vec[i-1])Vec[++tmp]=Vec[i];tot=tmp;
    top=0;Stk[++top]=Vec[1];Voot=Vec[1];Va[Voot]=0;
    for(int i=2;i<=tot;i++)
    {
        while(top && !In(Vec[i],Stk[top]))top--;
        Va[Vec[i]]=Stk[top];Vink(Stk[top],Vec[i]);
        // printf("VINK %d %d\n",Stk[top],Vec[i]);
        Stk[++top]=Vec[i];
    }
}
 
long long dp[M];
void Dp(int u)
{
    dp[u]=A[u];
    for(int i=Vead[u];i;i=V[i].to)
    {
        int v=V[i].v;if(v==Va[u])continue;
        Dp(v);
        dp[u]+=dp[v]?max(1ll,dp[v]-(dep[v]-dep[u])):0;
    }
    // printf("dp %d = %lld\n",u,dp[u]);
}
 
vector<int>Dv[M];
void Solve()
{
    dfs_Init(ROOT);re_dfs_Init(ROOT);
    for(int i=1;i<=n;i++)Dv[dep[i]].push_back(i);
    long long Ans=0;
    for(int i=0;i<n;i++)
    {
        if(Dv[i].empty())break;
        tot=0;for(unsigned int vi=0;vi<Dv[i].size();vi++)Vec[++tot]=Dv[i][vi];
        // for(int j=1;j<=tot;j++)printf("%d dep %d\n",Vec[j],i);
        Build_VT();Dp(Voot);
        Ans+=dp[Voot]?max(1ll,dp[Voot]-(dep[Voot]+1)):0;
        // printf("%d Ans+= %lld\n",i,max(1ll,dp[Voot]-(dep[Voot]+1)));
        clearv();for(unsigned int vi=0;vi<Dv[i].size();vi++)A[Dv[i][vi]]=0;
    }
    printf("%lld\n",Ans);
}
 
int main()
{
    scanf("%d%d",&n,&ROOT);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        Link(u,v);Link(v,u);
    }
    Solve();
    return 0;
}