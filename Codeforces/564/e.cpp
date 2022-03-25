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
const int maxn = 200000 + 5;
const int maxq = 3000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv(int x) {
    return qpow(x, mod - 2);
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

int n, m, a[maxn], w[maxn];
ll f[maxq][maxq];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int sa = 0, sb = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", w + i);
        if (a[i]) sa += w[i];
        else sb += w[i];
    }
    f[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= i; j++) {
            int a = sa + j, b = sb - (i - j);
            ll fm = inv(a + b);
            add(f[i + 1][j + 1], f[i][j] * a % mod * fm % mod);
            add(f[i + 1][j], f[i][j] * b % mod * fm % mod);
        }
    }
    ll ea = 0, eb = 0;
    for (int i = 0; i <= m; i++) {
        dbg(f[m][i]);
        add(ea, f[m][i] * (sa + i) % mod);
        add(eb, f[m][i] * (sb - (m - i)) % mod);
    }
    dbg(ea, eb);
    ll iva = inv(sa), ivb = inv(sb);
    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            printf("%lld\n", 1ll * w[i] * iva % mod * ea % mod);
        } else {
            printf("%lld\n", 1ll * w[i] * ivb % mod * eb % mod);
        }
    }
    return 0;
}