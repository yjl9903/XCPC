#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k, dis[maxn], vis[maxn], pre[maxn];
vector<int> edge[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        dis[i] = inf;
        if ((int)edge[i].size() == 1) {
            q.push(i);
            dis[i] = 1;
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: edge[u]) {
            if (dis[v] == inf) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    int mxd = 0;
    for (int i = 1; i <= n; i++) {
        mxd = max(mxd, dis[i]);
        assert(dis[i] != inf);
        pre[dis[i]]++;
    }
    for (int i = 1; i <= mxd; i++) {
        pre[i] += pre[i - 1];
        if (n - k <= pre[i]) {
            printf("%d\n", i);
            return 0;
        }
    }
    assert(0);
    return 0;
}