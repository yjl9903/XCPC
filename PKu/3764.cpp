#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

struct edge {
    int to, nxt, val;
} g[maxn * 2];
int head[maxn], tot;
void add(int u, int v, int w) {
    g[++tot].to = v;
    g[tot].nxt = head[u];
    g[tot].val = w;
    head[u] = tot;
}

int a[maxn];
void dfs(int u, int f) {
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f) continue;
        a[v] = a[u] ^ g[i].val;
        dfs(v, u);
    }
}

struct Trie {
    static const int M = 31;
    int ch[maxn * M][2], val[maxn * M], sz;
    void init() {
        ms(ch, 0); ms(val, 0); sz = 1;
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
    int query(int x) {
        int tot = x, ans = x, u = 0;
        for (int i = M - 1; i >= 0; i--) {
            bool b = x & (1ll << i);
            if (ch[u][0] && b) u = ch[u][0];
            else if (ch[u][1] && !b) tot ^= (1ll << i), u = ch[u][1];
            else if (ch[u][0]) u = ch[u][0];
            else if (ch[u][1]) tot ^= (1ll << i), u = ch[u][1];
            if (val[u]) ans = max(ans, tot);
        }
        return max(ans, tot);
    }
} trie;

int n;

int main() {
    while (scanf("%d", &n) == 1) {
        ms(head, 0); tot = 0;
        for (int i = 2, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w); u++; v++;
            add(u, v, w); add(v, u, w);
        }
        dfs(1, 0);
        trie.init();
        for (int i = 1; i <= n; i++) {
            trie.insert(a[i]);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) ans = max(ans, trie.query(a[i]));
        printf("%d\n", ans);
    }
    return 0;
}