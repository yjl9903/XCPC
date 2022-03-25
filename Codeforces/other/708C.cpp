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
const int maxn = 400000 + 5;

void gmax(int& a, int b) {
    if (a < b) a = b;
}
struct node {
    int fi = -1, se = -1;
    void insert(int x) {
        if (x >= fi) se = fi, fi = x;
        else if (x > se) se = x;
    }
    int get(int x) {
        if (x == fi) return se;
        return fi;
    }
} a[maxn];

int n, fa[maxn], down[maxn], up[maxn], siz[maxn], son[maxn];
vector<int> edge[maxn];

void dfs1(int u, int f) {
    siz[u] = 1; fa[u] = f;
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        gmax(down[u], down[v]);
        if (siz[v] <= n / 2) gmax(down[u], siz[v]);
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
    if (n - siz[u] > siz[son[u]]) son[u] = f;
}
void dfs2(int u, int f) {
    for (int v: edge[u]) {
        if (v == f) continue;
        if (siz[v] <= n / 2) a[u].insert(siz[v]);
        else a[u].insert(down[v]);
    }
    for (int v: edge[u]) {
        if (v == f) continue;
        if (n - siz[v] <= n / 2) up[v] = n - siz[v];
        else {
            up[v] = up[u];
            if (siz[v] <= n / 2) gmax(up[v], a[u].get(siz[v]));
            else gmax(up[v], a[u].get(down[v]));
        }
        dfs2(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    }
    dfs1(1, 0); dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        int f = 0, v = son[i];
        if (v == fa[i]) {
            if (n - siz[i] <= n / 2) f = 1;
            else if (n - siz[i] - up[i] <= n / 2) f = 1;
        } else {
            if (siz[v] <= n / 2) f = 1;
            else if (siz[v] - down[v] <= n / 2) f = 1;
        }
        putchar(f + '0'); putchar(' ');
    }
    return 0;
}