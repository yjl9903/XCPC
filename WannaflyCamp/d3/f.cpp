#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max_n=powl(10,20.0/3)+5;
const ll mod=998244353;
ll n;
bool p[max_n];
int prime[max_n];
int cnt;
ll f[max_n];
ll divisor[max_n];
ll g[max_n];
unordered_map<ll,ll> _f,_g;
void sieve()
{
    p[0]=p[1]=true;
    f[1]=1;
    divisor[1]=1;
    g[1]=1;
    for(int i=2;i<max_n;i++)
    {
        if(!p[i])
        {
            prime[cnt++]=i;
            f[i]=-2;
            divisor[i]=i;
            g[i]=2;
        }
        for(int j=0;j<cnt&&1ll*prime[j]*i<max_n;j++)
        {
            p[i*prime[j]]=true;
            if(i%prime[j]==0)
            {
                if(i==divisor[i])
                {
                    if(i==prime[j])f[i*prime[j]]=1;
                    else f[i*prime[j]]=0;
                    g[i*prime[j]]=g[i]+1;
                }
                else 
                {
                    f[i*prime[j]]=f[i/divisor[i]]*f[divisor[i]*prime[j]];
                    g[i*prime[j]]=g[i/divisor[i]]*g[divisor[i]*prime[j]];
                }
                divisor[i*prime[j]]=divisor[i]*prime[j];
                break;
            }
            else 
            {
                f[i*prime[j]]=f[i]*f[prime[j]];
                g[i*prime[j]]=g[i]*g[prime[j]];
                divisor[i*prime[j]]=prime[j];
            }
        }
    }
    for(int i=1;i<max_n;i++)f[i]+=mod+f[i-1],f[i]%=mod;
    for(int i=1;i<max_n;i++)g[i]+=g[i-1],g[i]%=mod;
}
ll gg(ll n)
{
    if(n<max_n)return g[n];
    if(_g.find(n)!=_g.end())return _g[n];
    ll res=0;
    for(ll l=1,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        if(r>n)r=n;
        res+=(r-l+1)%mod*(n/l)%mod,res%=mod;
    }
    //cout<<'g'<<' '<<res<<endl;
    return _g[n]=res;
}
ll cal(ll n)
{
    if(n<max_n)return f[n];
    if(_f.find(n)!=_f.end())return _f[n];
    ll res=1;
    for(ll l=2,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        if(r>n)r=n;
        res+=mod-(gg(r)+mod-gg(l-1))*cal(n/l)%mod;
        res%=mod;
    }
    return _f[n]=res;
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
        res+=cal(n/l)*(dd(r)+mod-dd(l-1))%mod;
        res%=mod;
    }
    return (res+mod)%mod;
}
int main()
{
    scanf("%lld",&n);
    sieve();
    //for(int i=1;i<=30;i++)cout<<f[i]<<' ';
   // cout<<'f'<<endl;
    printf("%lld\n",work(n));
    return 0;
}