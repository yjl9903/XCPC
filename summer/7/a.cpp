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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int c[20], w[] = { 0, 1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000 };

ll p, suf[20];

ll ans;
void dfs(int now, ll cnt, ll val) {
    if (val > p) return ;
    if (val == p) {
        ans = min(ans, cnt);
        return ;
    }
    if (now == 0) {
        return ;
    }
    // dbg(now, cnt, val);
    // if (now == 5 || now == 8) {
    if (true) {
        ll rest = p - val;
        ll nd = min(1ll * c[now], (rest / w[now]));
        dfs(now - 1, cnt + nd, val + 1ll * nd * w[now]);
        nd--;
        if (nd >= 0) {
            dfs(now - 1, cnt + nd, val + 1ll * nd * w[now]);
        }
    } else {
        ll rest = p - val;
        ll nd = min(1ll * c[now], (rest / w[now]));
        dfs(now - 1, cnt + nd, val + 1ll * nd * w[now]);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%lld", &p);
        ll sum = 0; ll cnt = 0;
        for (int i = 1; i <= 10; i++) scanf("%d", c + i), sum += 1ll * c[i] * w[i], cnt += c[i];
        if (sum < p) {
            puts("-1"); continue;
        }
        p = sum - p;
        // dbg(p, sum, cnt);
        ans = inf;
        dfs(10, 0, 0);
        if (ans == inf) puts("-1");
        else printf("%lld\n", cnt - ans);
    }
    return 0;
}