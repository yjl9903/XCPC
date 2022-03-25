#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100 + 5;

int n, m, tag, s, G[maxn][maxn], vis[maxn], ok[maxn];

ll ans; vector<int> stk, edge[maxn];
void dfs(int now, int c) {
    // ok[now] = 1;
    // dbg(now, c);
    if (c == s) {
        ans++; return ;
    }
    for (int v: edge[now]) {
        int f = 1;
        for (int x: stk) {
            if (G[v][x] == 0) {
                f = 0; break;
            }
        }
        if (f) {
            stk.push_back(v);
            dfs(v, c + 1);
            stk.pop_back();
        }
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        set<PII,int> st;
        scanf("%d%d%d", &n, &m, &s);
        ms(G, 0); ms(vis, 0); ms(ok, 0);
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            if (u > v) swap(u, v);
            if (!G[u][v]) {
                edge[u].push_back(v);
            }
            G[u][v] = G[v][u] = 1;
        }
        ans = 0;
        for (int i = 1; i <= n; i++) {
            stk.push_back(i);
            dfs(i, 1);
            stk.pop_back();
        }
        printf("%lld\n", ans);
    }
    return 0;
}