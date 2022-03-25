#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll mod=1000000007;
const int max_n=100005;
char c[max_n];
string s;
int T;
ll quick_pow(ll  a,ll b)
{
    ll res=1;
    while(b)
    {
        if(b&1)res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
ll work(string s,ll mod)
{
    ll res=0;
    for(int i=0;i<s.size();i++)
    {
        res=(res*10+s[i]-'0')%mod;
    }
    return res;
}
int main()
{
    scanf("%d",&T);
    ll ans;
    while(T--)
    {
        scanf(" %s",c);
        s=c;
        ll b=work(s,mod-1);
        ans=quick_pow(2ll,b);
        ans=ans*quick_pow(2ll,mod-2)%mod;
        printf("%lld\n",ans);
    }
    return 0;
}