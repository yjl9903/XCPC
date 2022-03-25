#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define ms(a,b) memset(a,b,sizeof(a))
#define msn(a,n,b) for(int i=0;i<=n;i++)a[i]=b
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define fi first
#define se second
using namespace std;
mt19937 rng_32(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
typedef double db;
const int mod=1e9+7;
const int seed=233;
const double PI=acos(-1.0);
const double eps=1e-7;
const int inf=0x3f3f3f3f;
const int max_n=100005;
ll ceil(ll x,ll y){if(x==0)return 0;if(y<0)x=-x,y=-y;bool sign=x>0;x=abs(x);return sign?(x+y-1)/y:-x/y;}
ll floor(ll x,ll y){if(x==0)return 0;if(y<0)x=-x,y=-y;bool sign=x>0;x=abs(x);return sign?x/y:-(x+y-1)/y;}
char str[max_n];
void rs(string& s){scanf(" %s",str);s=str;}
namespace {
    inline int Add(int x,int y){return (x+=y)>=mod?x-mod:x;}
    inline int Sub(int x,int y){return (x-=y)<0?x+mod:x;}
    inline int Mul(int x,int y) {return 1ll*x*y%mod;}
    inline int Pow(int x,int y=mod-2){int res=1;while(y){if(y&1)res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
/**********************head************************/
int n,l,p;
char s[max_n];
unordered_map<ll,int> dp,newdp;
bool check(ll x){
    return __builtin_popcountll(x)<=p;
}
int main(){
    scanf("%d%d%d",&n,&l,&p);
    scanf("%s",s+1);
    dp[0]=1;
    for(int i=1;i<=n;i++){
        newdp.clear();
        for(auto p:dp){
            ll x=p.fi;
            if(x>>(l-1)&1)x^=1ll<<(l-1);
            x<<=1;
            for(int j=0;j<2;j++){
                if(s[i]=='*'||s[i]-'0'==j){
                    if(check(x|j))newdp[x|j]=Add(newdp[x|j],p.second);
                }
            }
        }
        dp=newdp;
    }
    int ans=0;
    for(auto p:dp)ans=Add(ans,p.second);
    printf("%d\n",ans);
    return 0;
}