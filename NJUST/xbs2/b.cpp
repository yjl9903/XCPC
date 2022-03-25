#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int a, b, k;

namespace count {
    ll f[340000], g[340000];
    ll init(ll n){  
        ll i,j,m;  
        for(m=1;m*m<=n;++m)f[m]=n/m-1;  
        for(i=1;i<=m;++i)g[i]=i-1;  
        for(i=2;i<=m;++i){  
            if(g[i]==g[i-1])continue;  
            for(j=1;j<=min(m-1,n/i/i);++j){  
                if(i*j<m)f[j]-=f[i*j]-g[i-1];  
                else f[j]-=g[n/i/j]-g[i-1];  
            }  
            for(j=m;j>=i*i;--j)g[j]-=g[j/i]-g[i-1];  
        }  
        return f[1];
    }  
}
namespace Mobius {
    const int maxp = 100000 + 5;
    int mu[maxp], vis[maxp], prime[maxp], divsor[maxp], tot;
    void init() {
        mu[1] = 1;
        for (int i = 2; i < maxp; ++i) {
            if (!vis[i]) prime[++tot] = i, mu[i] = -1, divsor[i] = i;
            for (int j = 1; j <= tot && i * prime[j] < maxp; ++j) {
                vis[i * prime[j]] = 1;
                divsor[i * prime[j]] = prime[j];
                if (i % prime[j] == 0) {
                    mu[i * prime[j]] = 0;
                    break;
                }
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}
using namespace Mobius;

bool isprime(int k) {
    int top = (int)sqrt(k + 0.5);
    for (int i = 2; i <= top; i++) if (k % top == 0) return 0;
    return 1;
}

int p[maxn], cnt;
int cal(int x) {
    x /= k;
    int ans = x, m = (int)sqrt(x + 0.5);
    for (int i = 2; i <= x; i++) {
        if (divsor[i] >= k) continue;
        ans += mu[i] * x / i;
    }
    dbg(x, ans);
    return ans;
}

int main() {
    Mobius::init();
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &a, &b, &k);
        if (!isprime(k)) puts("0");
        else {
            // cout << cal(b) << ' ' << cal(a - 1) << endl;
            printf("%d\n", cal(b) - cal(a - 1));
        }
    }
    return 0;
}