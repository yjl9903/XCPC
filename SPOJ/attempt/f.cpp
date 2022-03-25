#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2e5+50;
const int inf=0x77777777;
typedef long long LL;
inline void rad(int &_){
    static char ch;bool mak=false;
    while(ch=getchar(),ch<'0'||ch>'9')if(ch=='-')mak=true;
    _=ch-48;
    while(ch=getchar(),ch<='9'&&ch>='0')_=_*10+ch-48;
    if(mak) _=-_;
}
int to[N<<1],las[N<<1],fir[N],ds[N<<1],cnt;
inline void add_edge(int u,int v,int a){
    to[++cnt]=v;las[cnt]=fir[u];fir[u]=cnt;ds[cnt]=a;
    to[++cnt]=u;las[cnt]=fir[v];fir[v]=cnt;ds[cnt]=a;
}
inline int max(int u,int v){return u>v?u:v;}
inline int min(int u,int v){return u<v?u:v;}
int VAL[N];
int n,k,m,x,y,z;
int f[N],dep[N],siz[N],vis[N];
int rot,Cnt,sum;
LL ans;
void grot(int u,int v){
    siz[u]=1;f[u]=0;
    for(int i=fir[u];i;i=las[i])
    if(to[i]!=v&&!vis[to[i]]){
        grot(to[i],u);
        siz[u]+=siz[to[i]];
        f[u]=max(f[u],siz[to[i]]);
    }
    f[u]=max(f[u],sum-siz[u]);
    if(f[u]<f[rot])rot=u;
}
struct node{
    int dis,val;
}sth[N];
int dis[N],val[N];
bool mmp(const node &u,const node &v){
    return u.val<v.val;
}
struct Tree{
    int F[N];
    void insert(int u,int val){
        for(int i=u;i<=n+2;i+=i&-i)F[i]=max(F[i],val);
    }
    void erase(int u){
        for(int i=u;i<=n+2;i+=i&-i)F[i]=0;
    }
    int Ans(int u){
        int ret=0;
        for(int i=u;i;i&=i-1)ret=max(ret,F[i]);
        return ret;
    }
}s;
void gsth(int u,int v,int a){
    if(val[u]>k-a)return;//剪枝
    sth[++Cnt]=(node){dis[u],val[u]};
    for(int i=fir[u];i;i=las[i])
    if(to[i]!=v&&!vis[to[i]]){
        dis[to[i]]=dis[u]+ds[i];
        val[to[i]]=val[u]+VAL[to[i]];
        gsth(to[i],u,a);
    }
}
void calc(int u,int Dis,int Val){
    int CCCC=2;
    Cnt=1;
    sth[1].dis=0;
    sth[1].val=0;
    s.insert(VAL[u]+1,0);
    //注意！
    for(int i=fir[u];i;i=las[i])
    if(!vis[to[i]]){
        dis[to[i]]=ds[i];
        val[to[i]]=VAL[to[i]];
        gsth(to[i],u,VAL[u]);
        for(int j=CCCC;j<=Cnt;j++)
            ans=max(ans,s.Ans(k-sth[j].val+1)+sth[j].dis);
        //查找最大值，更新答案
        for(int j=CCCC;j<=Cnt;++j)
            s.insert(sth[j].val+VAL[u]+1,sth[j].dis);
        //插入，尝试更新
        CCCC=Cnt+1;
    }
    for(int i=1;i<=Cnt;i++)
    s.erase(sth[i].val+VAL[u]+1);
    //最后别忘删除
}
void solve(int u){
    calc(u,0,0);vis[u]=1;
    for(int i=fir[u];i;i=las[i])
    if(!vis[to[i]]){
        rot=0;sum=siz[to[i]];
        grot(to[i],0);
        solve(rot);
    }
}
int main(){
    rad(n);rad(k);rad(m);
    for(int i=1;i<=m;i++){
        rad(x);
        VAL[x]=1;
    }
    for(int i=1;i<n;i++){
        rad(x);rad(y);rad(z);
        add_edge(x,y,z);
    }
    ans=0;//答案初始化为0！
    f[0]=sum=n;
    grot(1,0);
    solve(rot);
    printf("%lld\n",ans);
}