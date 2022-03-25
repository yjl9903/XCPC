#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200 + 5;

int n, k, a[maxn];
vector<int> edge[maxn];

int f[maxn][maxn];

void dfs(int u, int ff) {
    f[u][0] = a[u];
    for (int v: edge[u]) {
        if (v == ff) continue;
        dfs(v, u);
        vector<int> tmp(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i + j + 1 <= k) continue;
                tmp[min(i, j + 1)] = max(tmp[min(i, j + 1)], f[u][i] + f[v][j]);
            }
        }
        for (int i = 0; i <= n; i++) f[u][i] = tmp[i];
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int u, v, i = 2; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    int ans = 0;
    for (int i = 0; i <= n; i++) ans = max(ans, f[1][i]);
    cout << ans;
    return 0;
}