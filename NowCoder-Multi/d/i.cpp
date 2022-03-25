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
const int maxn = 200000 + 5;

int n, q;
char s[maxn];
int match[maxn];

namespace acam {
    static const int maxp = 2000000 + 5;
    int sz, ch[maxp][26];
    int node() {
        ms(ch[++sz], 0);
        return sz;
    }
    void clear() {
        sz = 0; node();
    }
    void insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        match[i] = u;
    }
    int fa[maxp], son[maxp], siz[maxp], dep[maxp], top[maxp];
    void dfs(int u, int f) {
        fa[u] = f;
        son[u] = 0;
        siz[u] = 1;
        dep[u] = dep[f] + 1;
        int m = -1;
        for (int i = 0; i < 26; i++) {
            if (!ch[u][i]) continue;
            int v = ch[u][i];
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) m = siz[v], son[u] = v;
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return ;
        dfs(son[u], u, tp);
        for (int i = 0; i < 26; i++) {
            if (!ch[u][i]) continue;
            int v = ch[u][i];
            if (v == son[u]) continue;
            dfs(v, u, v);
        }
    }
    void build() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    int query(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        int x = dep[u] < dep[v] ? u : v;
        return dep[x] - 1;
    }
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        acam::clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", s);
            acam::insert(s, i);
        }
        acam::build();
        scanf("%d", &q);
        printf("Case %d:\n", ++kase);
        int u, v;
        while (q--) {
            scanf("%d%d", &u, &v);
            u = match[u];
            v = match[v];
            printf("%d\n", acam::query(u, v));
        }
    }
    return 0;
}