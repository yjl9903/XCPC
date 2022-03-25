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
const int maxn = 800000 + 5;

int n, m, q, pre[maxn];
int head[maxn], nxt[maxn], tail[maxn];
vector<int> edge[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
      edge[i].clear();
      head[i] = i;
      tail[i] = i;
      nxt[i] = 0;
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      u++; v++;
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    scanf("%d", &q);
    for (int i = 0, x; i < q; i++) {
      scanf("%d", &x); x++;
      int rt = find(x);
      if (rt != x) continue;

      int nHead = 0, nTail = 0;
      for (int u = head[rt]; u; u = nxt[u]) {
        for (int v: edge[u]) {
          if (find(v) != rt) {
            assert(nxt[tail[find(v)]] == 0);
            if (nTail == 0) {
              nTail = tail[find(v)];
            }
            nxt[tail[find(v)]] = nHead;
            nHead = head[find(v)];

            head[find(v)] = 0;
            tail[find(v)] = 0;

            pre[find(v)] = rt;
          }
        }
      }
      head[rt] = nHead;
      tail[rt] = nTail;
      assert(nxt[tail[rt]] == 0);
    }
    for (int i = 1; i <= n; i++) {
      printf("%d%c", find(i) - 1, " \n"[i == n]);
    }
  }
  return 0;
}