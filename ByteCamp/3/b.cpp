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
const int maxn = 40 + 5;
const int maxs = 250 + 5;

int n, R, C, q;

namespace DSU {
  int pre[maxn], siz[maxn];
  void clear() {
    for (int i = 1; i <= n; i++) {
      pre[i] = i; siz[i] = 1;
    }
  }
  int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
  }
  bool join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (siz[x] > siz[y]) swap(x, y);
    pre[x] = y; siz[y] += siz[x];
    return true;
  }
}

struct Edge {
  int u, v, w;
  bool operator < (const Edge& b) const {
    return w < b.w;
  }
} e[maxs][maxs];

vector<Edge> join(const vector<Edge>& a, const vector<Edge>& b) {
  DSU::clear();
  vector<Edge> ans;
  int aS = a.size(), bS = b.size();
  for (int p1 = 0, p2 = 0; p1 < aS || p2 < bS; ) {
    auto doA = [&]() {
      if (DSU::join(a[p1].u, a[p1].v)) {
        ans.push_back(a[p1]);
      }
      p1++;
    };
    auto doB = [&]() {
      if (DSU::join(b[p2].u, b[p2].v)) {
        ans.push_back(b[p2]);
      }
      p2++;
    };
    if (p1 < aS && p2 < bS) {
      if (a[p1] < b[p2]) {
        doA();
      } else {
        doB();
      }
    } else if (p1 < aS) {
      doA();
    } else if (p2 < bS) {
      doB();
    }
  }
  return ans;
}

vector<Edge> st[8][maxs][maxs];

int main() {
  scanf("%d%d%d%d", &n, &R, &C, &q);
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      scanf("%d%d%d", &e[i][j].u, &e[i][j].v, &e[i][j].w);
      st[0][i][j].push_back(e[i][j]);
    }
  }
  for (int k = 1; k < 8; k++) {
    for (int i = 1; i + (1 << k) - 1 <= R; i++) {
      for (int j = 1; j + (1 << k) - 1 <= C; j++) {
        auto va = join(st[k - 1][i][j], st[k - 1][i][j + (1 << (k - 1))]);
        auto vb = join(st[k - 1][i + (1 << (k - 1))][j], st[k - 1][i + (1 << (k - 1))][j + (1 << (k - 1))]);
        st[k][i][j] = join(va, vb);
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    int x1, x2, y1, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    int k = __lg(min(x2 - x1 + 1, y2 - y1 + 1));
    auto va = join(st[k][x1][y1], st[k][x1][y2 - (1 << k) + 1]);
    auto vb = join(st[k][x2 - (1 << k) + 1][y1], st[k][x2 - (1 << k) + 1][y2 - (1 << k) + 1]);
    auto ans = join(va, vb);
    if ((1 << (k + 1)) < (x2 - x1 + 1)) {
      auto vc = join(st[k][x1 + (1 << k)][y1], st[k][x1 + (1 << k)][y2 - (1 << k) + 1]);
      ans = join(ans, vc);
    }
    if ((1 << (k + 1)) < (y2 - y1 + 1)) {
      auto vc = join(st[k][x1][y1 + (1 << k)], st[k][x2 - (1 << k) + 1][y1 + (1 << k)]);
      ans = join(ans, vc);
    }
    if (ans.size() + 1 == n) {
      int sum = 0;
      for (auto& e: ans) {
        sum += e.w;
      }
      printf("%d\n", sum);
    } else {
      puts("-1");
    }
  }
  return 0;
}