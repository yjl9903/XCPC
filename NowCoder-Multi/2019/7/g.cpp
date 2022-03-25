#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct fastIO {
    char s[100000]; int it,len;
    fastIO() { it = len = 0; }
    inline char get() {
        if (it < len) return s[it++];
        it = 0; len = fread(s, 1, 100000, stdin);
        if (len == 0) return EOF;
        else return s[it++];
    }
    bool notend() {
        char c = get();
        while(c == ' ' || c == '\n') c = get();
        if (it > 0) it--;
        return c != EOF;
    }
} buff;
inline int gi() {
    int r = 0; bool ng = 0; 
    char c = buff.get();
    while (c != '-' && (c < '0' || c > '9')) c = buff.get();
    if (c == '-') ng = 1, c = buff.get();
    while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
    return ng ? -r : r;
}

int n, m, w[maxn];
vector<int> edge[maxn], bag[maxn];
set<int> sts[maxn];

namespace hld {
    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& v: edge[u]) {
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
        for (auto& v: edge[u]) {
            if (v == f || v == son[u]) continue; // !
            dfs(v, u, v);
        }
    }
    void build() {
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
using hld::qlca;

const int sz = 350;
int stk[maxn], tot, bel[maxn], bcnt, key[maxn];
void dfs(int u, int f) {
    int bot = tot;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        if (tot - bot >= sz) {
            bcnt++; key[bcnt] = u;
            while (tot != bot) {
                bel[stk[tot--]] = bcnt;
            }
        }
    }
    stk[++tot] = u;
}

int main() {
    n = gi(); m = gi();
    for (int i = 1; i <= n; i++) w[i] = gi();
    for (int i = 2, u, v; i <= n; i++) {
        u = gi(); v = gi();
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    hld::build();
    while (tot) bel[stk[tot--]] = bcnt;
    for (int i = 1; i <= n; i++) {
        sts[bel[i]].insert(i);
        bag[bel[i]].push_back(i);
    }
    for (int T = 1, x, k; T <= m; T++) {
        // scanf("%d%d", &x, &k);
        x = gi(); k = gi();
        int id = bel[x], ans = 0;
        for (int u: bag[id]) {
            int g = qlca(u, x);
            if (u - k <= w[g]) ans = max(ans, u);
        }
        for (int i = 1; i <= bcnt; i++) {
            if (i == id) continue;
            int g = qlca(x, key[i]);
            auto it = sts[i].upper_bound(w[g] + k);
            if (it == sts[i].begin()) continue;
            it--;
            ans = max(ans, *it);
        }
        printf("%d\n", ans);
    }
    return 0;
}