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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, nn;
vector<int> lsh;
vector<PII> edge[maxn];

namespace hld {
    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp); // !
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f || v == son[u]) continue; // !
            dfs(v, u, v);
        }
    }
    void init() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
}

int tot, ls[maxn * 40], rs[maxn * 40], cnt[maxn * 40], root[maxn];
void update(int i, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre]; cnt[rt] = cnt[pre] + 1;
    if (l == r) return ;
    int m = (l + r) / 2;
    if (i <= m) update(i, ls[pre], lson);
    else update(i, rs[pre], rson);
}
int query(int i, int l, int r, int rt) {
    if (r <= i) return cnt[rt];
    int m = (l + r) / 2;
    if (i <= m) return query(i, lson);
    else return cnt[rt] - cnt[rs[rt]] + query(i, rson);
}
void dfs(int u, int f) {
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        int w = lower_bound(lsh.begin(), lsh.end(), x.second) - lsh.begin() + 1;
        update(w, root[u], 1, nn, root[v]);
        dfs(v, u);
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        lsh.push_back(w);
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    } hld::init();
    sort(lsh.begin(), lsh.end()); 
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = lsh.size();
    dfs(1, 0);
    while (q--) {
        int u, v, k; scanf("%d%d%d", &u, &v, &k);
        int kk = lower_bound(lsh.begin(), lsh.end(), k) - lsh.begin();
        if (lsh[kk] == k) kk++;
        if (kk == 0) {
            puts("0"); continue;
        }
        int g = hld::qlca(u, v);
        int s1 = query(kk, 1, nn, root[g]);
        int s2 = query(kk, 1, nn, root[u]);
        int s3 = query(kk, 1, nn, root[v]);
        // dbg(u, v, g, s1, s2, s3);
        printf("%d\n", s2 + s3 - 2 * s1);
    }
    return 0;
}