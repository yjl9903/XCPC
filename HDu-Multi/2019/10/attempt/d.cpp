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
typedef pair<ll,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 61;
const int maxn = 100000 + 5;

struct LinearBase {
    static const int maxl = 60;
    ll a[maxl + 5];
    int cnt; ll sum = 0;
    LinearBase() { cnt = sum = 0; ms(a, 0); }
    void clear() { cnt = sum = 0; ms(a, 0); }
    int insert(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (a[i]) x ^= a[i];
                else {
                    for (int k = 0; k < i; k++) 
                        if (x & (1ll << k)) x ^= a[k];
                    for (int k = i + 1; k < maxl; k++) 
                        if (a[k] & (1ll << i)) a[k] ^= x;
                    a[i] = x; cnt++;
                    return true;
                }
            }
        }
        return false;
    }
};

char s[maxn];
int n, q, pos[maxn];
ll w[maxn];
ll xorw[maxn], sumw[maxn], mn[maxn];
 
int fa[maxn << 1][21];
namespace sam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        tot = last = 1; ms(ch[1], 0);
    }
    int insert(int c) {
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i; i--) {
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
    }
    struct Edge {
        int to, nxt;
    } e[maxn << 1];
    int ecnt, head[maxn << 1];
    void adde(int u, int v) {
        e[++ecnt] = { v, head[u] };
        head[u] = ecnt;
    }
    void dfs(int u, int f) {
        if (u != 1) {
            int l = len[u] - len[f];
            if (l % 2) xorw[u] = w[cnt[u]];
            sumw[u] = l * w[cnt[u]];
            mn[u] = w[cnt[u]];
        } else {
            sumw[u] = xorw[u] = 0; mn[u] = inf;
        }

        fa[u][0] = f;
        for (int i = 1; i < 21; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            dfs(v, u);

            xorw[u] ^= xorw[v];
            sumw[u] += sumw[v];
            mn[u] = min(mn[u], mn[v]);
        }
    }
    void build() {
        rsort();
        ecnt = 0;
        for (int i = 0; i <= tot; i++) head[i] = 0;
        for (int i = 2; i <= tot; i++) adde(link[i], i);
        dfs(1, 0);
    }
}
using sam::link;
using sam::len;
using sam::cnt;
 
int get(int u, int l) {
    for (int i = 20; i >= 0; i--) {
        if (!fa[u][i]) continue;
        int v = fa[u][i];
        if (sam::len[v] >= l) u = v;
    }
    return u;
}
 
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        sam::clear();
        scanf("%d%s", &n, s + 1);
        for (int i = 1; i <= n; i++) {
            pos[i] = sam::insert(s[i] - 'a');
        }
        for (int i = 1; i <= n; i++) scanf("%lld", w + i);
        sam::build();
        scanf("%d", &q);
        int l, r;
        while (q--) {
            scanf("%d%d", &l, &r);
            int u = get(pos[r], r - l + 1);
            dbg(u, )
            ll ans = sumw[u];
            ll xo = xorw[u];
            ans -= (len[u] - len[link[u]]) * w[cnt[u]];
            ans += (len[u] + l - r) * w[cnt[u]];
            xo ^= (len[u] - len[link[u]]) % 2 ? w[cnt[u]] : 0;
            xo ^= (len[u] + l - r) % 2 ? w[cnt[u]] : 0;
            if (xo == 0) ans -= mn[u];
            // ll ans = (len[u] + l - r) * w[cnt[u]];
            // ll xo = (len[u] + l - r) % 2 ? w[cnt[u]] : 0;
            // ll mn = w[cnt[u]];
            // dbg(u, len[u], cnt[u]);
            // // dbg(u, ans, xo, mn);
            // if (link[u]) {
            //     int fa = link[u];
            //     ans += sumw[fa];
            //     xo ^= xorw[fa];
            //     mn = min(mn, ::mn[fa]);
            // }
            // if (xo == 0) ans -= mn;
            printf("%lld\n", ans);
        }
    }
    return 0;
}