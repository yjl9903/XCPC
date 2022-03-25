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

int n, m, dep[maxn];
vector<int> edge[maxn], bag[2];

void dfs(int u, int d) {
    dep[u] = d;
    bag[d % 2].push_back(u);
    for (int& v: edge[u]) {
        if (dep[v]) continue;
        dfs(v, d + 1);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
        }
        dfs(1, 1);
        if ((int)bag[0].size() < (int)bag[1].size()) {
            printf("%d\n", (int)bag[0].size());
            for (int& x: bag[0]) {
                printf("%d ", x);
            }
            puts("");
        } else {
            printf("%d\n", (int)bag[1].size());
            for (int& x: bag[1]) {
                printf("%d ", x);
            }
            puts("");
        }
        bag[0].clear(); bag[1].clear();
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); dep[i] = 0;
        }
    }
    return 0;
}