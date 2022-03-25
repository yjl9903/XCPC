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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int add(int& x, int y) {
    return (x += y) >= mod ? x -= mod : x;
}
inline int sub(int& x, int y) {
    return (x -= y) < 0 ? x += mod : x;
}
inline int mul(int& x, int y) {
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
    int w[maxn << 3], rev[maxn << 3];
    inline int build(int m) {
        int step = 0, n = 1;
        for (; n < m; n <<= 1) ++step;
        for (int i = 1; i < n; i++) 
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
        return n;  
    }
    inline void print(const Poly& a) {
        for (int x: a) printf("%d ", x);
        puts("");
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

int main() {
    int n, m; Poly a, b;
    scanf("%d%d", &n, &m);
    a.push_back(0);
    for (int i = 1; i <= m; i++) a.push_back(inv(i));
    b = a;
    // for (int i = 0, x; i <= n; i++) scanf("%d", &x), a.push_back(x);
    // for (int i = 0, x; i <= m; i++) scanf("%d", &x), b.push_back(x);
    // print(a); print(b);
    Poly ans = a * b;
    for (int x: a) printf("%d ", x);
    return 0;
}