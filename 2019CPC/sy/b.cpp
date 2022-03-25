#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, k, unsafe[maxn], pre[maxn], siz[maxn], val[maxn];
vector<int> edge[maxn];

int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    pre[x] = y; siz[y] += siz[x];
    return true;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
            pre[i] = i; 
            siz[i] = 1;
            unsafe[i] = val[i] = 0;
        }
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        for (int i = 1, x; i <= k; i++) {
            scanf("%d", &x); unsafe[x] = 1;
        }
        for (int i = 1; i <= n; i++) {
            if (unsafe[i]) continue;
            for (int v: edge[i]) {
                if (unsafe[v]) continue;
                join(i, v);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!unsafe[i]) continue;
            for (int v: edge[i]) {
                if (unsafe[v]) continue;
                if (find(v) == find(1)) continue;
                val[i] += siz[find(v)];
            }
        }
        double ans = siz[find(1)], mx = 0;
        for (int i = 1; i <= n; i++) {
            if (unsafe[i]) continue;
            if (find(i) != find(1)) continue;
            for (int v: edge[i]) {
                if (!unsafe[v]) continue;
                mx = max(mx, (double)val[v] / (double)edge[v].size());
            }
        }
        printf("%.8lf\n", ans + mx);
    }
    return 0;
}