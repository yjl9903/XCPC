#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 300000 + 5;

vector<int> edge[maxn];
int n, x, y, deg[maxn], siz[maxn];

ll ans = 0;
int dfs(int u, int f) {
    int c = 0, x = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        if (dfs(v, u) && c < 2) {
            c++; ans++;
        }
    }
    return c < 2;
}

int main(){
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    if (n == 2) return printf("%d", x), 0;
    if (n == 3) return printf("%d", x + min(x, y)), 0;
    if (x == y) return printf("%lld\n", 1ll * (n - 1) * x), 0;
    vector<int> leaf;
    for (int i = 1; i <= n; i++) if (deg[i] == 1) leaf.push_back(i);
    if (x < y) {
        dfs(1, 0);
        // cout << ans << endl;
        ans = 1ll * ans * x + 1ll * (n - 1 - ans) * y;
        cout << ans << endl;
    } else {
        int flag = 0;
        for (int i = 1; i <= n; i++) if (deg[i] == n - 1) flag = 1;
        if (flag) cout << 1ll * (n - 2) * y + x << endl;
        else cout << 1ll * (n - 1) * y << endl;
    }
    return 0;
}