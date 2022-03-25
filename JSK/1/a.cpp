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

int n, deg[maxn], fa[maxn];
vector<int> edge[maxn];

void dfs(int u, int f) {
    for (int& v: edge[u]) {
        if (v == f) continue;
        fa[v] = u;
        dfs(v, u);
    }
    deg[u] = (int)edge[u].size() - 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int tot = deg[i] + deg[j] + 1;
            if (fa[i] == j || fa[j] == i) tot--;
            ans = max(ans, tot);
        }
    }
    cout << ans << endl;
    return 0;
}