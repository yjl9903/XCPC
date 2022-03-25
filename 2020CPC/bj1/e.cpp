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

int n, m, a[maxn];
vector<int> bag[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  
  int a[maxn << 2], R[maxn << 2], cov[maxn << 2];
  
  void pushup(int rt) {
    a[rt] = min(a[rt << 1], a[rt << 1 | 1]);
    R[rt] = max(R[rt << 1], R[rt << 1 | 1]);
  }
  
  void pushdown(int rt, int m, int r) {
    if (cov[rt] == -1) return ;
    int t = cov[rt];
    R[rt << 1] = R[rt << 1 | 1] = t;
    a[rt << 1] = t - m + 1;
    a[rt << 1 | 1] = t - r + 1;
    cov[rt << 1] = cov[rt << 1 | 1] = t;
    cov[rt] = -1;
  }

  void build(int l = 1, int r = n, int rt = 1) {
    cov[rt] = -1;
    if (l == r) {
      R[rt] = inf;
      a[rt] = R[rt] - l + 1;
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
  }

  void update(int qL, int qR, int x, int l = 1, int r = n, int rt = 1) {
    if (qL <= l && r <= qR) {
      R[rt] = x;
      a[rt] = x - r + 1;
      cov[rt] = x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m, r);
    if (qL <= m) update(qL, qR, x, lson);
    if (qR > m) update(qL, qR, x, rson);
    pushup(rt);
  }

  int qpos(int k, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      if (R[rt] <= k) return l;
      else return l - 1;
    }
    int m = (l + r) / 2;
    pushdown(rt, m, r);
    if (R[rt << 1] <= k) return qpos(k, rson);
    else return qpos(k, lson);
  }

  int ans() {
    return a[1];
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    bag[a[i]].push_back(i);
  }
  SegT::build();
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < bag[i].size(); j++) {
      int pos = bag[i][j];
      int last = j == 0 ? 1 : bag[i][j - 1] + 1;
      // max i satisfy R[i] <= pos
      int R = i == 1 ? pos : SegT::qpos(pos);
      if (last <= R) {
        SegT::update(last, R, pos);
      }
    }
    {
      int last = bag[i].back() + 1;
      if (last <= n) {
        SegT::update(last, n, inf);
      }
    }
    printf("%d ", SegT::ans());
  }
  return 0;
}