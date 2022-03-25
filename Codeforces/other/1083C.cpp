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

int n, q, a[maxn], pos[maxn], fa[maxn];
vector<int> edge[maxn];

namespace LCA {
  const int L = 19;
  
  int st[maxn], ed[maxn], dep[maxn];
  int euler[maxn * 2], cnt;
  int dp[L][maxn * 2];

  void dfs(int u, int f) {
    euler[++cnt] = u;
    st[u] = cnt;
    for (int v: edge[u]) {
      if (v == f) continue;
      dep[v] = dep[u] + 1;
      dfs(v, u);
      euler[++cnt] = u;
    }
    ed[u] = cnt;
  }
  void build(int rt = 1) {
    dep[rt] = 0;
    cnt = 0;
    dfs(rt, 0);
    for (int i = 1; i <= cnt; i++) {
      dp[0][i] = euler[i];
    }
    for (int j = 1; j < L; j++) {
      for (int i = 1; i + (1 << j) <= cnt + 1; i++) {
        int l = dp[j - 1][i];
        int r = dp[j - 1][i + (1 << (j - 1))];
        if (dep[l] < dep[r]) {
          dp[j][i] = l;
        } else {
          dp[j][i] = r;
        }
      }
    }
  }
  int qlca(int u, int v) {
    int l = st[u], r = st[v];
    if (l > r) swap(l, r);
    int k = __lg(r - l + 1);
    int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
    if (dep[x] < dep[y]) {
      return x;
    } else {
      return y;
    }
  }
  int qdis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[qlca(u, v)];
  }
}

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  PII join(int x, int y, int z) {
    int xy = LCA::qdis(x, y);
    int yz = LCA::qdis(y, z);
    int xz = LCA::qdis(x, z);
    if (xy + yz == xz) {
      return { x, z };
    } else if (xz + yz == xy) {
      return { x, y };
    } else if (xy + xz == yz) {
      return { y, z };
    } else {
      return { -1, -1 };
    }
  }

  struct Node {
    int x, y;
    bool flag;

    Node operator+ (const Node& rhs) const {
      if (!flag || !rhs.flag) {
        return { -1, -1, false };
      }
      auto res = join(x, rhs.x, rhs.y);
      if (res.first != -1 && res.second != -1) {
        res = join(y, res.first, res.second);
        if (res.first != -1 && res.second != -1) {
          return { res.first, res.second, true };
        }
      }
      return { -1, -1, false };
    }
  } a[maxn << 2];

  void build(int l = 0, int r = n - 1, int rt = 1) {
    if (l == r) {
      a[rt].x = pos[l];
      a[rt].y = pos[r];
      a[rt].flag = true;
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  void update(int x, int u, int l = 0, int r = n - 1, int rt = 1) {
    if (l == r) {
      a[rt].x = u;
      a[rt].y = u;
      return ;
    }
    int m = (l + r) / 2;
    if (x <= m) update(x, u, lson);
    else update(x, u, rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  int query(Node x, int l = 0, int r = n - 1, int rt = 1) {
    if (l == r) {
      return l;
    }
    int m = (l + r) / 2;
    auto tmp = x + a[rt << 1];
    if (tmp.flag) {
      return query(tmp, rson);
    } else {
      return query(x, lson);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pos[a[i]] = i;
  }
  for (int i = 2; i <= n; i++) {
    scanf("%d", fa + i);
    edge[fa[i]].push_back(i);
  }
  LCA::build();
  SegT::build();
  scanf("%d", &q);
  while (q--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      SegT::update(a[x], y);
      SegT::update(a[y], x);
      swap(a[x], a[y]);
      pos[a[x]] = x;
      pos[a[y]] = y;
    } else if (op == 2) {
      if (SegT::a[1].flag) {
        printf("%d\n", n);
      } else {
        auto res = SegT::query({ pos[0], pos[0], true });
        printf("%d\n", res);
      }
    }
  }
  return 0;
}