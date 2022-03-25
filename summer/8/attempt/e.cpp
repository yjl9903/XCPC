#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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

int n, m, tag, s, G[maxn][maxn], vis[maxn], deg[maxn];

int ans; vector<int> stk;
void dfs(int now, int c) {
    if (c == s) {
        ans++; return ;
    }
    if (c + n - now + 1 < s) return ;
    if (now == n + 1) return ;
    int flag = 1;
    for (int x: stk) {
        // dbg(tag, G[x][now]);
        if (G[x][now] != tag) {
            flag = 0; break;
        }
    }
    if (flag && deg[now] >= s - 1) {
        stk.push_back(now);
        dfs(now + 1, c + 1);
        stk.pop_back();
    }
    dfs(now + 1, c);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &s);
        ms(G, 0); ms(vis, 0); ms(deg, 0);
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            G[u][v] = G[v][u] = 1;
        }
        int sum = 0;
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
            if (G[i][j]) {
                sum++; deg[i]++; deg[j]++;
            }
        }
        tag = 1;
        if (sum > n * (n - 1) / 4) {
            tag = 0;
            for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) G[i][j] ^= 1;
        }
        ans = 0;
        dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}