#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>
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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
const int maxq = 300000 + 5;

mt19937_64 rnd(time(nullptr));

struct DSU {
  int pre[maxn], siz[maxn], cnt;
  ull val[maxn];
  int find(int x) {
    while (x != pre[x]) x = pre[x];
    return x;
  }
  vector<PII> sta;
  void init(int n) {
    sta.clear(); cnt = 0;
    for (int i = 1; i <= n; i++) {
      pre[i] = i; siz[i] = 1; val[i] = 0;
    }
  }
  bool join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return 0;
    if (siz[x] > siz[y]) swap(x, y);
    pre[x] = y;
    siz[y] += siz[x];
    if (val[x]) cnt--;
    if (val[y]) cnt--;
    val[y] ^= val[x];
    if (val[y]) cnt++;
    sta.push_back({x, y});
    return 1;
  }
  void undo() {
    PII tp = sta.back(); sta.pop_back();
    int x = tp.first, y = tp.second;
    pre[x] = x;
    siz[y] -= siz[x];
    if (val[y]) cnt--;
    val[y] ^= val[x];
    if (val[x]) cnt++;
    if (val[y]) cnt++;
  }
  void add(int u, ull x) {
    u = find(u);
    if (val[u]) cnt--;
    val[u] ^= x;
    if (val[u]) cnt++;
  }
} h;

int n, q, qu[maxq], qv[maxq];
bool isq[maxq], ans[maxq];
ull val[maxq];

struct E {
  int id, nxt;
} e[(int)2e7 + 5];
int tot, ehead[maxq << 2], qhead[maxq << 2];

void add(int tp, int u, int v) {
  if (tp) {
    e[++tot] = { v, qhead[u] };
    qhead[u] = tot;
  } else {
    e[++tot] = { v, ehead[u] };
    ehead[u] = tot;
  }
}

void build(int l = 1, int r = q, int rt = 1) {
  ehead[rt] = qhead[rt] = 0;
  if (l == r) return ;
  int m = (l + r) / 2;
  build(lson); build(rson);
}
void insert(int L, int R, bool tp, int x, int l = 1, int r = q, int rt = 1) {
  if (L <= l && r <= R) {
    add(tp, rt, x);
    return ;
  }
  int m = (l + r) / 2;
  if (L <= m) insert(L, R, tp, x, lson);
  if (R > m) insert(L, R, tp, x, rson);
}

void solve(int l = 1, int r = q, int rt = 1) {
  int ecnt = 0;
  for (int i = ehead[rt]; i; i = e[i].nxt) {
    int id = e[i].id;
    ecnt += h.join(qu[id], qv[id]);
  }
  for (int i = qhead[rt]; i; i = e[i].nxt) {
    int id = e[i].id;
    h.add(qu[id], val[id]);
    h.add(qv[id], val[id]);
  }
  if (l == r) {
    ans[l] = !h.cnt;
    for (int i = qhead[rt]; i; i = e[i].nxt) {
      int id = e[i].id;
      h.add(qu[id], val[id]);
      h.add(qv[id], val[id]);
    }
    while (ecnt--) {
      h.undo();
    }
    return ;
  }
  int m = (l + r) / 2;
  solve(lson); solve(rson);
  for (int i = qhead[rt]; i; i = e[i].nxt) {
    int id = e[i].id;
    h.add(qu[id], val[id]);
    h.add(qv[id], val[id]);
  }
  while (ecnt--) {
    h.undo();
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    build(); h.init(n);
    tot = 0;
    map<PII,int> te, tq;
    for (int i = 1, op, u, v; i <= q; i++) {
      scanf("%d", &op);
      val[i] = rnd();
      if (op == 5) {
        isq[i] = true;
      } else {
        isq[i] = false;
        scanf("%d%d", &u, &v);
        qu[i] = u; qv[i] = v;
        if (op == 1) {
          te[{u, v}] = i;
        } else if (op == 2) {
          insert(te[{u, v}], i, 0, te[{u, v}]);
          te.erase({u, v});
        } else if (op == 3) {
          tq[{u, v}] = i;
        } else if (op == 4) {
          insert(tq[{u, v}], i, 1, tq[{u, v}]);
          tq.erase({u, v});
        }
      }
    }
    for (auto& x: te) {
      insert(x.second, q, 0, x.second);
    }
    for (auto& x: tq) {
      insert(x.second, q, 1, x.second);
    }
    solve();
    for (int i = 1; i <= q; i++) {
      if (isq[i]) {
        puts(ans[i] ? "YES" : "NO");
      }
    }
  }
  return 0;
}