#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <functional>
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
const int maxn = (1 << 20) + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

int n, q, rt, f[maxn];
vector<int> edge[20];

int main() {
    scanf("%d%d%d", &n, &q, &rt);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        u--; v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int ss = 1 << n;
    for (int s = 0; s < ss; s++) {
        function<PII(int,int)> dfs = [&](int u, int ff) -> PII {
            if (s >> u & 1) return { 0, 0 };
            int suma = 0, sumb = 0;
            for (int v: edge[u]) {
                if (v == ff) continue;
                PII x = dfs(v, u);
                suma = add(suma, x.first);
                sumb = add(sumb, x.second);
            }
            int d = (int)edge[u].size();
            return { inv(sub(d, suma)), mul(add(d, sumb), inv(sub(d, suma))) };
        };
        PII r = dfs(rt - 1, -1);
        if (__builtin_popcount(s) % 2) {
            f[s] = r.second;
        } else {
            f[s] = sub(0, r.second);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < ss; s++) {
            if (s >> i & 1) f[s] = add(f[s], f[s ^ (1 << i)]);
        }
    }
    while (q--) {
        int k, x, s = 0; scanf("%d", &k);
        while (k--) {
            scanf("%d", &x); s |= 1 << (x - 1);
        }
        printf("%d\n", f[s]);
    }
    return 0;
}