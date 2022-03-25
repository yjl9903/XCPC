#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

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

using Poly = vector<int>;

namespace PolyOP {
    int rev[maxn << 3];
    inline int build(int m) {
        int step = 0, n = 1;
        for (; n < m; n <<= 1) ++step;
        for (int i = 1; i < n; i++) 
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
        return n;  
    }
    inline void print(const Poly& a) {
        #ifdef XLor
            for (int x: a) printf("%d ", x);
            puts("");
        #endif
    }
    void ntt(int a[], int n, int op = 0) {
        for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int h = 2; h <= n; h <<= 1) {
            int wn = qpow(3, (mod - 1) / h);
            if (op == -1) wn = inv(wn);
            for (int i = 0; i < n; i += h) {
                int w = 1;
                for (int j = i; j < i + h / 2; j++) {
                    int u = a[j], t = 1ll * a[j + h / 2] * w % mod;
                    a[j] = (u + t) % mod;
                    a[j + h / 2] = (u - t + mod) % mod;
                    w = 1ll * w * wn % mod;
                }
            }
        }
        if (op == -1) {
            ll rn = inv(n);
            for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * rn % mod;
        }
    }
    Poly operator * (const Poly& a, const Poly& b) {
        static int aa[maxn << 3], bb[maxn << 3];
        int lim = build((int)a.size() + (int)b.size() - 1);
        for (int i = 0; i < (int)a.size(); i++) aa[i] = a[i];
        for (int i = (int)a.size(); i < lim; i++) aa[i] = 0;
        for (int i = 0; i < (int)b.size(); i++) bb[i] = b[i];
        for (int i = (int)b.size(); i < lim; i++) bb[i] = 0;
        ntt(aa, lim); ntt(bb, lim);
        for (int i = 0; i < lim; i++) aa[i] = 1ll * aa[i] * bb[i] % mod;
        ntt(aa, lim, -1);
        Poly ans;
        for (int i = 0; i < (int)a.size() + (int)b.size() - 1; i++) ans.push_back(aa[i]);
        return ans;
    }
}
using namespace PolyOP;

namespace Comb {
    const int maxc = 2000000 + 5;
    int f[maxc], inv[maxc], finv[maxc];
    void init() {
        inv[1] = 1;
        for (int i = 2; i < maxc; i++) 
            inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
        f[0] = finv[0] = 1; 
        for (int i = 1; i < maxc; i++) {
            f[i] = f[i - 1] * 1ll * i % mod;
            finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
        }
    }
    int C(int n, int m) {
        if (m < 0 || m > n) return 0;
        return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
    }
}
using Comb::C;

int n, m;

int main() {
    Comb::init();
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        Poly a(n + 1, 0); vector<int> cnt(4, 0);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1, op; i <= m; i++) scanf("%d", &op), cnt[op]++;
        for (int k = 1; k <= 3; k++) {
            if (cnt[k] == 0) continue;
            Poly b(n + 1, 0);
            for (int i = 0; i <= n; i += k) {
                b[i] = C(i / k + cnt[k] - 1, i / k);
            }
            a = a * b; a.resize(n + 1);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) ans ^= 1ll * i * a[i];
        printf("%lld\n", ans);
    }
    return 0;
}