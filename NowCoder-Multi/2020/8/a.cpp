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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

int n, m, q, ans[maxn];
map<int,int> fan[maxn];

namespace DSU {
  int pre[maxn], siz[maxn], ans;
  vector<PII> sta;
  void init() {
    ans = n + m;
    sta.clear();
    for (int i = 1; i <= n + m; i++) {
      pre[i] = i; siz[i] = 1;
    }
  }
  int find(int x) {
    while (x != pre[x]) x = pre[x];
    return x;
  }
  int join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return 0;
    if (siz[x] > siz[y]) swap(x, y);

    pre[x] = y;
    siz[y] += siz[x];
    ans--;

    sta.push_back({x, y});
    return 1;
  }
  void undo() {
    PII tp = sta.back();
    sta.pop_back();
    int x = tp.first, y = tp.second;
    pre[x] = x;
    siz[y] -= siz[x];
    ans++;
  }
}

int baS = 0, fanS = 0, cnt[maxn];
void add(int x) {
  if (cnt[x] == 0) {
    if (x <= n) {
      baS++;
    } else {
      fanS++;
    }
  }
  cnt[x]++;
}
void del(int x) {
  cnt[x]--;
  if (cnt[x] == 0) {
    if (x <= n) {
      baS--;
    } else {
      fanS--;
    }
  }
}

vector<PII> egs[maxn << 2];
void update(int L, int R, PII e, int l = 1, int r = q, int rt = 1) {
  if (L <= l && r <= R) {
    egs[rt].push_back(e);
    return ;
  }
  int m = (l + r) / 2;
  if (L <= m) update(L, R, e, lson);
  if (R > m) update(L, R, e, rson);
}

void dfs(int l = 1, int r = q, int rt = 1) {
  // dbg(l, r);
  // insert
  int cnt = 0;
  for (auto e: egs[rt]) {
    int r = DSU::join(e.first, e.second);
    // dbg(e.first, e.second - n, r, DSU::ans);
    cnt += r;
    add(e.second);
    add(e.first);
  }
  if (l == r) {
    if (fanS < m) {
      ans[l] = -1;
    } else {
      ans[l] = DSU::ans - (n - baS);
    }
  } else {
    int m = (l + r) / 2;
    dfs(lson);
    dfs(rson);
  }
  // undo
  while (cnt--) {
    DSU::undo();
  }
  for (auto e: egs[rt]) {
    del(e.first);
    del(e.second);
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  DSU::init();
  for (int i = 1; i <= n; i++) {
    int k, x;
    scanf("%d", &k);
    while (k--) {
      scanf("%d", &x);
      fan[i][x] = 1;
    }
  }
  for (int i = 1, x, y; i <= q; i++) {
    scanf("%d%d", &x, &y);
    if (fan[y].count(x)) {
      if (fan[y][x] < i) {
        // dbg(fan[y][x], i - 1, y, x);
        update(fan[y][x], i - 1, { y, x + n });
      }
      fan[y].erase(x);
    } else {
      fan[y][x] = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (auto x: fan[i]) {
      // dbg(x.second, q, i, x.first);
      update(x.second, q, { i, x.first + n });
    }
  }
  dfs();
  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}