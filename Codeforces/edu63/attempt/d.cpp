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
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, x;
ll a[maxn];

ll cal() {
    ll mx = 0, dp = 0;
    for (int i = 1; i <= n; i++) {
        if (dp < 0) dp = a[i];
        else dp += a[i];
        if (dp > mx) mx = dp;
    }
    return mx;
}

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
    if (x > 0) {
        cout << 1ll * x * cal() << endl;
    } else {
        ll ans = cal();
        ll dp = 0, mx = 0;
        int op = 1, aop = 0, aed = 0;
        for (int i = 1; i <= n; i++) {
            if (dp < 0) dp = -a[i], op = i;
            else dp += -a[i];
            if (dp > mx) mx = dp, aop = op, aed = i;
        }
        // dbg(mx, aop, aed);
        if (aop) {
            for (int i = aop; i <= aed; i++) a[i] *= 1ll * x;
            ans = max(ans, cal());
        }
        cout << ans << endl;
    }
    return 0;
}