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

int n, dep[maxn];
vector<int> edge[maxn];

void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    }
    dfs(1, 0);
    int rt, mx = 0;
    for (int i = 1; i <= n; i++) if (dep[i] > mx) mx = dep[i], rt = i;
    dfs(rt, 0);
    mx = 0; for (int i = 1; i <= n; i++) mx = max(mx, dep[i]);
    if (mx % 3 != 2) puts("First");
    else puts("Second");
    return 0;
}