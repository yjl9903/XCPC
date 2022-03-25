#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
const int max_n=100005;
int Sqr;
ll n;
int cnt;
bool p[max_n];
int pri[max_n];
int m;
ll w[max_n*2];
int id1[max_n*2],id2[max_n*2];
ll pre[max_n];
ll g[max_n*2],h[max_n*2],s[max_n*2];
void sieve(int n)
{
    p[0]=p[1]=true;
    for(int i=2;i<=n;i++)
    {
        if(!p[i])pri[++cnt]=i;//decided
        for(int j=1;j<=cnt&&1ll*pri[j]*i<=n;j++)
        {
            p[i*pri[j]]=true;
            if(i%pri[j]==0)break;
        }
    }
}
void init()
{
    Sqr=sqrt(n);
    m=0;
    ll i,j;
    for(i=1;i<=n;i=j+1)
    {
        w[++m]=n/i;
        g[m]=(w[m]-1)%mod;
        j=n/(n/i);
        if(w[m]<=Sqr)id1[w[m]]=m;
        else id2[n/w[m]]=m;
    }
    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;1ll*pri[i]*pri[i]<=w[j];j++)
        {
            int k=(w[j]/pri[i]<=Sqr)?id1[w[j]/pri[i]]:id2[n/(w[j]/pri[i])];
            g[j]=g[j]+mod-1ll*(g[k]+mod-i+1)%mod,g[j]%=mod;
        }
    }
    for(int i=1;i<=m;i++)g[i]=mod+g[i]*(-2)%mod,g[i]%=mod;
}
ll getid(ll x,ll y){return x*max_n+y;}
map<ll,ll> biao;
ll f(ll e)
{
    if(e==1)return -2;
    else if(e==2)return 1;
    else return 0;
}
ll S(ll x,ll y)
{
    if(biao.find(getid(x,y))!=biao.end())return biao[getid(x,y)];
    if(x<=1||x<pri[y])return 0;
    int k=x<=Sqr?id1[x]:id2[n/x];
    ll res=g[k]-(y-1)*(-2)+mod;//decided by f(x)
    res%=mod;
    for(int i=y;i<=cnt&&1ll*pri[i]*pri[i]<=x;i++)
    {
        ll t1=pri[i],t2=1ll*pri[i]*pri[i];
        for(int e=1;t2<=x;e++,t1=t2,t2*=pri[i])
        {
            if(e>2)break;
            res+=f(e)*S(x/t1,i+1)%mod+f(e+1);//decided by f(x)
        }
    }
    return biao[getid(x,y)]=(res%mod+mod)%mod;
}
ll dd(ll x)
{
    x%=mod;
    return x*x%mod;
}
ll work(ll n)
{
    ll res=0;
    for(ll l=1,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        if(r>n)r=n;
        ll tmp;
        tmp=S(n/l,1)+1;
        res+=tmp*(dd(r)+mod-dd(l-1))%mod;
        res%=mod;
    }
    return res;
}
int main()
{
    sieve(max_n-1);
    scanf("%lld",&n);
    init();
    //printf("%lld\n",(1+S(n,1))%mod);
   // cout<<S(n)+1<<endl;
    printf("%lld\n",work(n));
    return 0;
}