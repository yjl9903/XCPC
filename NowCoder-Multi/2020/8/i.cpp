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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

namespace hk {
  int n, ans;
  int dx[maxn], dy[maxn];
  int linkx[maxn], linky[maxn];
  int head[maxn], to[maxn], nxt[maxn], ecnt;

  void clear(int N) {
    n = N; ecnt = ans = 0;
    ms(linkx, 0xff); ms(linky, 0xff); ms(head, 0);
  }
  void adde(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    if (linkx[u] == -1 && linky[v] == -1) {
      linkx[u] = v;
      linky[v] = u;
      ans++;
    }
  }
  bool bfs() {
    bool res = 0;
    static int q[maxn], l, r;

    ms(dx, 0); ms(dy, 0);
    l = r = 0;
    for (int i = 1; i <= n; i++)
      if (linkx[i] == -1) q[r++] = i;

    while (l < r) {
      int x = q[l++];
      for (int i = head[x]; i; i = nxt[i]) {
        if (!dy[to[i]]) {
          dy[to[i]] = dx[x] + 1;
          if (linky[to[i]] == -1) res = 1;
          else dx[q[r++] = linky[to[i]]] = dy[to[i]] + 1;
        }
      }
    }
    return res;
  }
  bool dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
      if (dx[u] + 1 == dy[to[i]]) {
        dy[to[i]] = 0;
        if (linky[to[i]] == -1 || dfs(linky[to[i]])) {
          linky[to[i]] = u;
          linkx[u] = to[i];
          return true;
        }
      }
    }
    return false;
  }
  int match(int n) {
    // clear(n): 1 ~ n
    while (bfs()) {
      for (int i = 1; i <= n; i++) {
        if (linkx[i] == -1) ans += dfs(i);
      }
    }
    return ans;
  }
}

int n, a[maxn], b[maxn];

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    hk::clear(n * 3);
    
    map<int,int> mp;
    int tot = n;
    auto gid = [&mp, &tot](int x) {
      if (mp.count(x)) {
        return mp[x];
      } else {
        return mp[x] = ++tot;
      }
    };
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", a + i, b + i);
      hk::adde(i, gid(a[i]));
      hk::adde(i, gid(b[i]));
    }
    printf("Case #%d: %d\n", ++kase, hk::match(n * 3));
  }
  return 0;
}