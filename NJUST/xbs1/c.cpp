#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
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
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n; ll k;
ll a[maxn];

struct Trie {
    static const int M = 63;
    int ch[maxn * M][2], val[maxn * M], siz[maxn * M], sz;
    void init() {
        ms(ch, 0); ms(val, 0); ms(siz, 0); sz = 1;
    }
    void insert(int x) {
        int u = 0;
        for (int i = M - 1; i >= 0; i--) {
            bool b = x & (1ll << i);
            if (!ch[u][b]) ch[u][b] = sz++;
            u = ch[u][b];
        }
        val[u]++;
    }
    void dfs(int u) {
        siz[u] = val[u];
        if (ch[u][0]) {
            dfs(ch[u][0]); siz[u] += siz[ch[u][0]];
        }
        if (ch[u][1]) {
            dfs(ch[u][1]); siz[u] += siz[ch[u][1]];
        }
    }
    ll query(ll t, ll mx) {
        ll cnt = 0; int u = 0;
        for (int i = M - 1; i >= 0; i--) {
            bool b = t & (1ll << i), b2 = mx & (1ll << i);
            if (b == b2) {
                if (ch[u][0]) {
                    if (b) cnt += siz[ch[u][0]];
                    u = ch[u][0];
                } else {
                    if (b) cnt += siz[ch[u][1]];
                    return cnt;
                }
            } else {
                if (ch[u][1]) {
                    if (!b) cnt += siz[ch[u][0]];
                    u = ch[u][1];
                } else {
                    // dbg('?', b, cnt);
                    if (!b) cnt += siz[ch[u][0]];
                    return cnt;
                }
            }
        }
        return cnt + val[u];
    }
} trie;

void dfs1(int u, int f) {
    for (int& v: edge[u]) {
        if (v == f) continue;
        a[v] ^= a[u];
        dfs1(v, u);
    }
}

ll check(ll x) {
    ll cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += trie.query(a[i], x);
    }
    // dbg(x, cnt);
    return cnt;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%lld", &n, &k);
        trie.init();
        for (int i = 1; i <= n; i++) edge[i].clear(); 
        for (int i = 2; i <= n; i++) {
            int p; ll w; scanf("%d%lld", &p, &w);
            edge[p].push_back(i); a[i] = w;
        }
        dfs1(1, 0);
        for (int i = 1; i <= n; i++) trie.insert(a[i]);
        trie.dfs(0);
        ll l = 0, r = (1ll << 62) - 1, ans = 0;
        while (l <= r) {
            ll m = l + (r - l) / 2ll;
            if (check(m) > k) ans = m, r = m - 1;
            else l = m + 1;
        }
        // for (int i = 1; i <= n; i++) {
        //     dbg(a[i], trie.query(a[i], 2));
        // }
        printf("%lld\n", ans);
    }
    return 0;
}