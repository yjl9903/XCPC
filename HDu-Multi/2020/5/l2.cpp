#include<bits/stdc++.h>
#define FastIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define inf 0x3f3f3f3f
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repp(i,a,b) for(int i=a;i<=b;i++)
#define rep1(i,a,b) for(int i=a;i>=b;i--)
#define mem(gv) memset(gv,0,sizeof(gv))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define QAQ 0
#define miaojie
#ifdef miaojie
  #define dbg(args...) do {cout << #args << " : "; err(args);} while (0)
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#else
  #define dbg(...)
#endif

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pLL;
const ll mod=998244353;
const int maxn=5e6+22;

ll T,n,ans[maxn];

ll powwmod(ll a,ll b){
    ll ans=1,base=a%mod;
    while(b){
        if(b&1)
            ans=(ans*base)%mod;
        base=(base*base)%mod;
        b>>=1;
    }
    return ans;
}
ll inv(ll a){
    return powwmod(a,mod-2);
}

int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        ll bas=1;
        for(ll i=1;i<=n;i++) ans[i]=0;
        for(ll i=1;i<n;i+=2){
            ll f=i*inv(i+1)%mod;
            bas=bas*f%mod;
        }
        ans[n]=bas;
        
        int pt=n;
        for(ll i=1;i<=n/2;i++){
            ll f=(n+1ll-i*2ll) * inv(n-i) %mod;
            ans[pt-1]=ans[pt]*f%mod;
            pt--;
        }
        for(ll i=1;i<=n;i++){
            printf("%lld",ans[i]);
            if(i==n) printf("\n");
            else printf(" ");
        }
    }    
    return QAQ;
}