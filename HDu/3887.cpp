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
const int maxn = 100000 + 5;

int n, rt;
vector<int> edge[maxn];

int a[maxn];
inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    for (; i <= n; i += lowbit(i)) a[i] += x;
}
inline int query(int i) {
    int r = 0;
    for (; i; i -= lowbit(i)) r += a[i];
    return r;
}

int ans[maxn], tin[maxn], tout[maxn], tot;
void dfs(int u, int f) {
    tin[u] = ++tot;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
    }
    tout[u] = tot;
}

int main() {
    while (scanf("%d%d", &n, &rt) == 2 && n && rt) {
        tot = 0;
        for (int i = 1; i <= n; i++) edge[i].clear(), a[i] = 0;
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
        }
        dfs(rt, 0);
        for (int i = 1; i <= n; i++) {
            if (i > 1) putchar(' ');
            printf("%d", query(tout[i]) - query(tin[i] - 1));
            update(tin[i], 1);
        }
        puts("");
    }
    return 0;
}