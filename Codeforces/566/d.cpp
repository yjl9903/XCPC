#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, deg[maxn], vis[maxn], dep[maxn];
vector<int> edge[maxn];

int check(int u) {
    int last = -1;
    for (int& v: edge[u]) {
        if (last == -1) last = deg[v];
        else {
            if (deg[v] != last) return 0;
        }
    }
    queue<PII> q; q.push({u, 0});
    int flag = 1; vector<PII> v;
    while (!q.empty()) {
        auto tp = q.front(); q.pop();
        v.push_back(tp);
        vis[tp.first] = 1;
        if (dep[tp.second] == -1) {
            dep[tp.second] = deg[tp.first];
        } else {
            if (deg[tp.first] != dep[tp.second]) {
                flag = 0; break;
            }
        }
        for (int& v: edge[tp.first]) {
            if (vis[v]) continue;
            q.push({v, tp.second + 1});
        }
    }
    for (auto& x: v) {
        vis[x.first] = 0;
        dep[x.second] = -1;
    }
    return flag;
}

int main() {
    ms(dep, -1);
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    for (int i = 1; i <= n; i++) {
        if (check(i)) return printf("%d\n", i), 0;
    }
    puts("-1");
    return 0;
}