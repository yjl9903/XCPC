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
const int maxn = 1000 + 5;

vector<int> edge[maxn];
int n, m;

int sg[maxn];
int dfs(int u) {
    if (sg[u] != -1) return sg[u];
    vector<int> vis(n + 1, 0);
    for (int& v: edge[u]) {
        vis[dfs(v)] = 1;
    }
    for (int i = 0; i <= n; i++) if (!vis[i]) return sg[u] = i;
}

int main() {
    ms(sg, -1);
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) {
            int m, x; scanf("%d", &m);
            while (m--) {
                scanf("%d", &x); edge[i].push_back(++x);
            }
        }
        while (scanf("%d", &m) == 1) {
            if (m == 0) break;
            int ans = 0, x;
            while (m--) {
                scanf("%d", &x); ans ^= dfs(++x);
            }
            if (ans) puts("WIN");
            else puts("LOSE");
        }
        for (int i = 1; i <= n; i++) edge[i].clear(), sg[i] = -1;
    }
    return 0;
}