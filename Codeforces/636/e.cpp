#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, a, b, c;
ll p[maxn];
vector<int> edge[maxn];

int disA[maxn], disB[maxn], disC[maxn];

void bfs(int s, int dis[]) {
  for (int i = 1; i <= n; i++) dis[i] = inf;
  queue<int> q; q.push(s); dis[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v: edge[u]) {
      if (dis[v] > dis[u] + 1) {
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 1; i <= m; i++) {
      scanf("%I64d", p + i);
    }
    sort(p + 1, p + 1 + m);
    for (int i = 1; i <= m; i++) {
      p[i] += p[i - 1];
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    bfs(a, disA); bfs(b, disB); bfs(c, disC);
    int mnd = disB[a];
    ll ans = 1e18;
    for (int i = 1; i <= n; i++) {
      // if (disB[i] + disA[i] == mnd) {
      if (mnd + disC[i] <= m) {
        ans = min(ans, p[disB[i]] + p[mnd + disC[i]]);
      }
      // }
    }
    // mnd = disB[c];
    // for (int i = 1; i <= n; i++) {
    //   if (disB[i] + disC[i] == mnd) {
    //     if (mnd + disA[i] <= m) {
    //       ans = min(ans, p[disB[i]] + p[mnd + disA[i]]);
    //     }
    //   }
    // }
    // dbg(mnd, p[mnd], ans);
    printf("%I64d\n", ans);
  }
  return 0;
}