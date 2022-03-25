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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 50 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

int n, m;
int op[maxn][maxn];

ll f[2][2][2], g[2][2][2], inv2;
ll cal(int a, int b, int c) {
    ms(f, 0);
    f[0][0][0] = 1;
    // dbg(a, b, c);
    for (int i = 1; i <= m; i++) {
        ms(g, 0);
        int f1 = 0, f2 = 0, f3 = 0;
        if (op[i][a]) f1 = 1;
        if (op[i][b]) f2 = 1;
        if (op[i][c]) f3 = 1;
        // dbg(f1, f2, f3);
        for (int x = 0; x < 2; x++) for (int y = 0; y < 2; y++) for (int z = 0; z < 2; z++) {
            // dbg(x, y, z, f[x][y][z]);
            add(g[x ^ f1][y ^ f2][z ^ f3], f[x][y][z] * inv2 % mod);
            add(g[x][y][z], f[x][y][z] * inv2 % mod);
        }
        swap(f, g);
    }
    return f[1][1][1];
}

int main() {
    inv2 = qpow(2, mod - 2);
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++) {
            int k, x; scanf("%d", &k);
            while (k--) {
                scanf("%d", &x);
                op[i][x] = 1;
            }
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    ans = (ans + cal(i, j, k)) % mod;
                }
            }
        }
        ans = ans * qpow(2, m) % mod;
        // cout << ans << '\n';
        printf("Case #%d: %lld\n", ++kase, ans);
        for (int i = 1; i <= m; i++) ms(op[i], 0);
    }
    return 0;
}