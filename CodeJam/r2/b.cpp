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

int n, m, rlen[maxn], ans[maxn], ord[maxn];
int len[maxn];
vector<PII> edge[maxn];

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      edge[i].clear(); len[i] = ord[i] = -1;
    }
    len[1] = 0;
    vector<PII> rks, lens;
    for (int i = 2, x; i <= n; i++) {
      scanf("%d", &x);
      rlen[i] = -1;
      if (x > 0) {
        rlen[i] = x;
        lens.push_back({ x, i });
      } else {
        ord[i] = -x - 1;
        rks.push_back({ -x - 1, i });
      }
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back({ v, i });
      edge[v].push_back({ u, i });
      ans[i] = -1;
    }

    // sort(begin(rks), end(rks));
    // sort(begin(lens), end(lens));
    // for (int i = 0, j = 0, li = 0, tot = 0; i < (int)rks.size(); i = j) {
    //   for (; li < rks[i].first - i; li++) {
    //     if (li && lens[li].first == lens[li - 1].first) {
    //       ord[lens[li].second] = ord[lens[li - 1].second];
    //     } else {
    //       ord[lens[li].second] = tot;
    //     }
    //     tot++;
    //   }
    //   while (j < (int)rks.size() && rks[i].first == rks[j].first) j++;
    // }

    rks.clear();
    for (int i = 2; i <= n; i++) {
      dbg(i, ord[i]);
      assert(ord[i] != -1);
      rks.push_back({ ord[i], i });
    }
    sort(begin(rks), end(rks));
    for (int i = 0, j = 0; i < (int)rks.size(); i = j) {
      while (j < (int)rks.size() && rks[i].first == rks[j].first) j++;
      int mx = 0;
      for (int k = i; k < j; k++) {
        int u = rks[k].second;
        for (auto& x: edge[u]) {
          int v = x.first;
          if (len[v] == -1) continue;
          mx = max(mx, len[v] + 1);
        }
      }
      for (int k = i; k < j; k++) {
        int u = rks[k].second;
        for (auto& x: edge[u]) {
          int v = x.first;
          int id = x.second;
          if (len[v] == -1) continue;
          ans[id] = mx - len[v];
          assert(ans[id] > 0);
        }
      }
      for (int k = i; k < j; k++) {
        int u = rks[k].second;
        len[u] = mx;
      }
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