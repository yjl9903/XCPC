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

int n, m, rlen[maxn], rk[maxn], ans[maxn];
vector<PII> edge[maxn];

int dep[maxn], fa[maxn], faId[maxn], faL[maxn];
void bfs() {
  fa[1] = 0; dep[1] = 0;
  vector<int> que; que.push_back(1);
  for (int i = 0; i < (int)que.size(); i++) {
    int u = que[i];
    for (auto& x: edge[u]) {
      int v = x.first;
      if (dep[v] > dep[u] + 1) {
        dep[v] = dep[u] + 1;
        fa[v] = u;
        faId[v] = x.second;
        faL[v] = 1;
        que.push_back(v);
      }
    }
  }
}

int getLen(int u) {
  int ans = 0;
  while (u) {
    ans += faL[u];
    assert(faL[u] <= (int)1e6);
    u = fa[u];
  }
  return ans;
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      edge[i].clear(); dep[i] = inf;
    }
    vector<PII> rks, lens;
    for (int i = 2, x; i <= n; i++) {
      scanf("%d", &x);
      if (x > 0) {
        rlen[i] = x;
        lens.push_back({ x, i });
      } else {
        rk[i] = -x - 1;
        rks.push_back({ -x - 1, i });
      }
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back({ v, i });
      edge[v].push_back({ u, i });
      ans[i] = -1;
    }

    bfs();
    sort(begin(rks), end(rks));
    sort(begin(lens), end(lens));
    for (int i = 0, j = 0; i < (int)rks.size(); i = j) {
      while (j < (int)rks.size() && rks[i].first == rks[j].first) j++;
      int mxlen = 0;
      for (int k = 0; k < rks[i].first - i; k++) {
        mxlen = max(mxlen, getLen(lens[k].second) + 1);
      }
      for (int k = i; k < j; k++) {
        mxlen = max(mxlen, getLen(rks[k].second));
      }
      dbg(rks[i].first, mxlen);
      for (int k = i; k < j; k++) {
        int u = rks[k].second;
        int fL = getLen(fa[u]);
        dbg(u, fL);
        faL[u] = mxlen - fL;
      }
    }

    for (int i = 1; i <= n; i++) {
      dbg(i, fa[i], faL[i]);
    }

    printf("Case #%d:", ++kase);
    for (int i = 1; i <= m; i++) {
      if (ans[i] == -1) {
        printf(" 1000000");
      } else {
        printf(" %d", ans[i]);
      }
    }
    puts("");
  }
  return 0;
}