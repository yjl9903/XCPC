#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
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
const int maxn = 500 + 5;

int inv[maxn];
namespace {
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
    inline int invl(int x) {
        return qpow(x, mod - 2);
    }
}

int n, rt, b[maxn];
vector<int> edge[maxn];

using Poly = vector<int>;

namespace PolyOpe {
    Poly operator+(const Poly& a, const Poly& b) {
        int n = (int)a.size(), m = (int)b.size();
        Poly ans(max(n, m), 0);
        for (int i = 0; i < max(n, m); i++) {
            if (i < n) ans[i] = add(ans[i], a[i]);
            if (i < m) ans[i] = add(ans[i], b[i]);
        }
        return ans;
    }
    Poly& operator+=(Poly& a, const int x) {
        if (a.empty()) a = (Poly){ x };
        else a[0] = add(a[0], x);
        return a;
    }
    Poly operator-(const Poly& a, const Poly& b) {
        int n = (int)a.size(), m = (int)b.size();
        Poly ans(max(n, m), 0);
        for (int i = 0; i < max(n, m); i++) {
            if (i < n) ans[i] = add(ans[i], a[i]);
            if (i < m) ans[i] = sub(ans[i], b[i]);
        }
        return ans;
    }
    Poly operator*(const Poly& a, const Poly& b) {
        int n = (int)a.size(), m = (int)b.size();
        Poly ans(n + m - 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i + j] = add(ans[i + j], mul(a[i], b[j]));
            }
        }
        return ans;
    }
    Poly Int(const Poly& a) {
        int n = (int)a.size();
        Poly ans(n + 1);
        for (int i = 0; i < n; i++) {
            ans[i + 1] = mul(inv[i + 1], a[i]);
        }
        return ans;
    }
    int eval(const Poly& p, int x) {
        if (x < 0) x += mod;
        int ans = 0, tot = 1;
        for (int y: p) {
            ans = add(ans, mul(y, tot));
            tot = mul(tot, x);
        }
        return ans;
    }
}
using namespace PolyOpe;

struct PDF {
    static const int R = 1e9 + 1;

    // f(x) = ps[i](x) in [rs[i - 1], rs[i]]
    // rs[-1] = -R
    vector<Poly> ps;
    vector<int> rs;
    int n = 0;

    PDF() {  }
    PDF(vector<Poly> p, vector<int> r) {
        ps = p; rs = r;
        n = (int)p.size();
    }

    PDF operator*(const PDF& y) {
        vector<Poly> nps;
        vector<int> nrs;
        int left = -R;
        for (int a = 0, b = 0; a < n && b < y.n; ) {
            nps.push_back(ps[a] * y.ps[b]);
            nrs.push_back(min(rs[a], y.rs[b]));
            left = nrs.back();
            while (a < n && rs[a] == left) a++;
            while (b < y.n && y.rs[b] == left) b++;
        }
        return PDF(nps, nrs);
    }

    PDF Int() {
        vector<Poly> nps(n);
        vector<int> nrs(n);
        int C = 0, left = -R;
        for (int i = 0; i < n; i++) {
            nps[i] = PolyOpe::Int(ps[i]);
            nrs[i] = rs[i];
            nps[i] += sub(C, eval(nps[i], left));
            C = eval(nps[i], nrs[i]); 
            // nrs[i] < 0 !!!
            left = nrs[i];
        }
        return PDF(nps, nrs);
    }
};

int ivb[maxn];
PDF dfs(int u) {
    PDF pdf({ Poly(0), Poly(1, ivb[u]), Poly(0) }, { -b[u], 0, PDF::R });
    for (int v: edge[u]) pdf = pdf * dfs(v);
    return pdf.Int();
}

int main() {
    for (int i = 1; i < maxn; i++) inv[i] = invl(i);
    scanf("%d", &n);
    for (int i = 1, fa; i <= n; i++) {
        scanf("%d%d", b + i, &fa);
        if (fa == 0) rt = i;
        else edge[fa].push_back(i);
        ivb[i] = invl(b[i]);
    }
    PDF ans = dfs(rt);
    cout << ans.ps[ans.n - 1][0];
    return 0;
}