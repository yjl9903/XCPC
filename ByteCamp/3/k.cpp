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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int inf = (int)2.1e9 + 1;
const int maxn = 200000 + 5;

int n, R, C, xx[maxn], yy[maxn], hh[maxn], ans[maxn];

struct Event {
  int x, y, z;
  bool operator < (const Event& b) {
    if (x != b.x) return x < b.x;
    return y < b.y;
  }
  int calX(int f = 1) const {
    return x + f * y - z;
  }
  int calY(int f = 1) const {
    return x + f * y + z;
  }
} b[maxn];

bool check(int n) {
  vector<Event> que;
  bool flag = (xx[1] + yy[1] + hh[1]) % 2;
  for (int i = 1; i <= n; i++) {
    if ((xx[i] + yy[i] + hh[i]) % 2 != flag) {
      return false;
    }
    ans[i] = 0;
    que.push_back({ xx[i], yy[i], hh[i] });
  }
  flag = true;
  sort(begin(que), end(que));
  auto cmp = [](const Event& a, const Event& b) {
    return a.y < b.y;
  };
  function<void(int,int)> dfs = [&](int l, int r) {
    if (!flag) return ;
    if (l >= r) return ;
    int m = (l + r) / 2;
    dbg(l, r);
    for (int i = l; i <= r; i++) {
      b[i] = que[i];
      dbg(b[i].x, b[i].y, b[i].z);
    }
    sort(b + l, b + m + 1, cmp); sort(b + m + 1, b + r + 1, cmp);
    int mX = -inf, mY = -inf;
    for (int i = m + 1, j = l; i <= r; i++) {
      for (; j <= m && b[j].y <= b[i].y; j++) {
        mX = max(mX, b[j].calX()); mY = max(mY, b[j].calY());
      }
      if (b[i].calX() < mX || b[i].calY() < mY) {
        flag = false;
        return ;
      }
    }
    mX = -inf; mY = -inf;
    for (int i = r, j = m; i > m; i--) {
      for (; j >= l && b[j].y >= b[i].y; j--) {
        mX = max(mX, b[j].calX(-1)); mY = max(mY, b[j].calY(-1));
      }
      if (b[i].calX(-1) < mX || b[i].calY(-1) < mY) {
        flag = false;
        return ;
      }
    }
    dfs(l, m); dfs(m + 1, r);
  };
  dfs(0, n - 1);
  return flag;
}

int main() {
  scanf("%d%d%d", &n, &R, &C);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", xx + i, yy + i, hh + i);
  }
  // check(2);
  int l = 2, r = n, ans = 1;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) {
      ans = m; l = m + 1;
    } else {
      r = m - 1;
    }
  }
  if (ans == n) {
    puts("bravo komisijo");
  } else {
    printf("%d\n", ans + 1);
  }
  return 0;
}