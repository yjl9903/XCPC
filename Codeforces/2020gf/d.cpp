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
const int maxn = 200000 + 5;

int n, m;
PII a[maxn], b[maxn];

struct Info {
  int x, y, id;
  bool operator<(const Info& b) const {
    return x < b.x;
  }
};

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  int a[maxn << 2];
  void build(int l = 1, int r = n, int rt = 1) {
    a[rt] = inf;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson);
    build(rson);
  }
  void update(int i, int x, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = min(a[rt], x);
      return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }
  int ans() {
    return a[1];
  }
}

int main() {
  scanf("%d%d", &n, &m);
  SegT::build();
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &b[i].first, &b[i].second);
  }
  sort(b + 1, b + 1 + m, [&](PII x, PII y) {
    if (x.first != y.first) {
      return x.first < y.first;
    } else {
      return x.second > y.second;
    }
  });
  vector<PII> stk;
  for (int i = 1; i <= m; i++) {
    while (!stk.empty() && b[i].second >= stk.back().second) {
      stk.pop_back();
    }
    stk.push_back(b[i]);
  }
  vector<Info> evs;
  for (int i = 1; i <= n; i++) {
    {
      int dy = stk.front().second + 1 - a[i].second;
      evs.push_back({ 0, max(dy, 0), i });
    }
    {
      int dx = stk.back().first + 1 - a[i].first;
      evs.push_back({ max(dx, 0), 0, i });
    }
    for (int j = 1; j < stk.size(); j++) {
      int tx = stk[j - 1].first + 1;
      int ty = stk[j].second + 1;
      evs.push_back({ max(tx - a[i].first, 0), max(ty - a[i].second, 0), i });
    }
  }
  sort(begin(evs), end(evs));
  int ans = inf;
  for (auto ev: evs) {
    SegT::update(ev.id, ev.y);
    int Y = SegT::ans();
    if (Y < inf) {
      ans = min(ans, ev.x + Y);
    }
  }
  printf("%d\n", ans);
  return 0;
}