#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 300000 + 5;

int ceil(int x, int y) {
    return x / y + (x % y > 0 ? 1 : 0);
}

int n, m, k, a[maxn];
ll pre[maxn];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pre[i] = pre[i - 1] + a[i];
    // for (int i = 1; i <= n; i++) cout << pre[i] << ' '; cout << endl;
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        vector<ll> v;
        int j, tot;
        dbg(i);
        for (j = i, tot = 1; j <= n; j += m, tot++) {
            ll mx = -inf;
            for (int k = j; k < j + m && k <= n; k++) mx = max(mx, pre[k]);
            v.push_back(mx - 1ll * k * tot);
            dbg(mx, mx - 1ll * k * tot);
        }
        ll mx = -inf;
        for (j -= m, tot--; j >= i; j -= m, tot--) {
            mx = max(v.back(), mx); v.pop_back();
            ans = max(ans, mx - pre[j - 1] + 1ll * k * (tot - 1));
            // dbg(mx, j - 1, pre[j - 1], mx - pre[j - 1] + 1ll * k * (tot - 1));
        }
    }
    cout << ans;
    return 0;
}