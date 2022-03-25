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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct BIT {
  int a[maxn];
  void update(int i, int x) {
    for (; i < maxn; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
} f;

struct Query {
  int x, y, id, tp;
  bool operator < (const Query& b) const {
    if (x != b.x) return x > b.x;
    if (y != b.y) return y < b.y;
    return abs(tp) < abs(b.tp);
  }
};
vector<Query> que;

int n, q, a[maxn], ans[maxn], ch[maxn][2];
int tot, dfn[maxn], pos[maxn];

void dfs(int u) {
  int L = tot + 1;
  if (ch[u][0]) {
    int v = ch[u][0]; dfs(v);
  }
  tot++; dfn[u] = tot; pos[tot] = u;
  if (ch[u][1]) {
    int v = ch[u][1]; dfs(v);
  }
  que.push_back({ L, tot, dfn[u], 0 });
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &ch[i][0], &ch[i][1]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  dfs(1);
  set<PII> seg; int beg = 1;
  for (int i = 1; i <= n; i++) {
    int u = pos[i], v = pos[i + 1];
    if (i == n || a[u] > a[v]) {
      seg.insert({ beg, i });
      que.push_back({ beg, i, 0, 1 });
      beg = i + 1;
    }
  }
  for (int i = 1; i <= q; i++) {
    int k, x; scanf("%d%d", &k, &x);
    int id = dfn[k];
    auto it = seg.upper_bound({ id, inf });
    assert(it != seg.begin()); it--;

    auto del = [&](int a, int b) {
      // dbg("del", a, b);
      seg.erase({ a, b });
      que.push_back({ a, b, i, -1 });
    };
    auto add = [&](int a, int b) {
      // dbg("add", a, b);
      seg.insert({ a, b });
      que.push_back({ a, b, i, 1 });
    };

    int L = it->first, R = it->second;
    // dbg(id, x, L, R);

    del(L, R); add(id, id);
    if (L < id) {
      add(L, id - 1);
    }
    if (id < R) {
      add(id + 1, R);
    }

    L = R = id;
    it = seg.find({ id, id });

    if (it != seg.begin()) {
      auto itL = it; itL--;
      if (a[pos[itL->second]] <= x) {
        del(L, R);
        L = itL->first;
        del(itL->first, itL->second);
        add(L, R);
        it = seg.find({ L, R });
      }
    }

    auto itR = it; itR++;
    if (itR != seg.end()) {
      if (x <= a[pos[itR->first]]) {
        del(L, R);
        R = itR->second;
        del(itR->first, itR->second);
        add(L, R);
      }
    }

    a[k] = x;
  }
  sort(begin(que), end(que));
  for (auto& q: que) {
    if (q.tp == 0) {
      f.update(q.y, 1);
    } else {
      ans[q.id] += q.tp * f.query(q.y);
    }
  }
  for (int i = 1; i <= q; i++) {
    ans[i] += ans[i - 1];
    printf("%d\n", ans[i]);
  }
  return 0;
}