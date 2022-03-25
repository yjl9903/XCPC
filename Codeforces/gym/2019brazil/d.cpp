#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k, fa[maxn], dep[maxn];
vector<int> edge[maxn];

int rid[maxn], tin[maxn], tout[maxn], tot, vis[maxn];
void dfs(int u) {
    tin[u] = ++tot; rid[tot] = u;
    for (int v: edge[u]) dep[v] = dep[u] + 1, dfs(v);
    tout[u] = tot;
}

struct Info {
    int mx, pos;
    Info operator+(const Info& b) {
        if (mx > b.mx) return (Info){mx, pos};
        else return (Info){b.mx, b.pos};
    }
} a[maxn << 2];

int tag[maxn << 2];
void build(int l, int r, int rt) {
    if (l == r) {
        a[rt] = (Info){dep[rid[l]], rid[l]};
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
}
void pushdown(int rt) {
    if (!tag[rt]) return ;
    int t = tag[rt];
    a[rt << 1].mx += t;
    tag[rt << 1] += t;
    a[rt << 1 | 1].mx += t;
    tag[rt << 1 | 1] += t;
    tag[rt] = 0;
}
void update(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
        tag[rt]--; a[rt].mx -= 1;
        return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
}

int main() {
    scanf("%d%d", &n, &k);
    dep[1] = 1;
    for (int i = 2; i <= n; i++) {
        scanf("%d", fa + i);
        edge[fa[i]].push_back(i);
    }
    dfs(1); build(1, n, 1);
    int ans = 0;
    for (int i = 1; i <= k && ans < n; i++) {
        int d = a[1].mx;
        ans += d; int u = a[1].pos;
        while (d--) {
            update(tin[u], tout[u], 1, n, 1);
            u = fa[u];
        }
    }
    printf("%d\n", ans);
    return 0;
}