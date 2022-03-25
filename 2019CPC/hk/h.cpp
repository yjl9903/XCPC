#include <iostream>
#include <cstdio>
#include <cassert>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;
const int maxm = 1000000 + 5;

int n, nn, q, ans[maxm];
int ap[maxn], a[maxn];

vector<int> lsh;
int gid(int x) {
  return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
}

struct Query {
  int op, x, y, h;
} all[maxm];

vector<tuple<int,int,int> > que[maxn];
vector<int> stks[maxm * 4];
void build(int l = 1, int r = nn, int rt = 1) {
  stks[rt].clear();
  if (l == r) return ;
  int m = (l + r) / 2;
  build(lson); build(rson);
}
void insert(int x) {
  int ti = ap[x], val = a[x];
  if (ti > q) return ;
  function<void(int,int,int)> dfs = [&](int l, int r, int rt) {
    auto& stk = stks[rt];
    while (!stk.empty() && ap[stk.back()] >= ti) stk.pop_back();
    stk.push_back(x); // stack with appear time up
    if (l == r) return ;
    int m = (l + r) / 2;
    if (val <= m) dfs(lson);
    else dfs(rson);
  };
  dfs(1, nn, 1);
}
int query(int L, int id, int h) {
  // check whether appear time < id, and location >= L
  auto check = [&](const vector<int>& stk) -> bool {
    int l = 0, r = (int)stk.size() - 1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (stk[m] >= L && ap[stk[m]] < id) return true;
      if (stk[m] < L) l = m + 1;
      else r = m - 1;
    }
    return false;
  };
  int ok = 0;
  function<void(int,int,int)> qmx = [&](int l, int r, int rt) {
    if (ok || stks[rt].empty()) return ;
    if (r <= h) {
      if (!check(stks[rt])) return ;
      if (l == r) {
        ok = l; return ;
      }
    }
    int m = (l + r) / 2;
    if (h > m) qmx(rson);
    qmx(lson);
  };
  function<void(int,int,int)> qmn = [&](int l, int r, int rt) {
    if (ok || stks[rt].empty()) return ;
    if (l >= h) {
      if (!check(stks[rt])) return ;
      if (l == r) {
        ok = l; return ;
      }
    }
    int m = (l + r) / 2;
    if (h <= m) qmn(lson);
    qmn(rson);
  };
  int ans = inf;
  qmx(1, nn, 1);
  if (ok) ans = lsh[h - 1] - lsh[ok - 1];
  ok = 0; qmn(1, nn, 1);
  if (ok) ans = min(ans, lsh[ok - 1] - lsh[h - 1]);
  return ans < inf ? ans : -1;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    lsh.clear();
    for (int i = 0; i <= n; i++) {
      que[i].clear(); ap[i] = q + 1;
    }
    for (int i = 1; i <= q; i++) {
      scanf("%d", &all[i].op);
      if (all[i].op == 0) {
        scanf("%d%d", &all[i].x, &all[i].h);
      } else if (all[i].op == 1) {
        scanf("%d%d%d", &all[i].x, &all[i].y, &all[i].h);
      }
      lsh.push_back(all[i].h);
    }
    sort(begin(lsh), end(lsh));
    lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
    nn = (int)lsh.size(); build();
    for (int i = 1; i <= q; i++) {
      if (all[i].op == 0) {
        ap[all[i].x] = i; // i-th pos appear time
        a[all[i].x] = gid(all[i].h); // value on i-th pos
      } else if (all[i].op == 1) {
        que[all[i].y].emplace_back(all[i].x, gid(all[i].h), i);
      }
    }
    for (int i = 1; i <= n; i++) {
      insert(i);
      for (auto& q: que[i]) {
        int l, h, id; tie(l, h, id) = q;
        ans[id] = query(l, id, h);
      }
    }
    for (int i = 1; i <= q; i++) {
      if (!all[i].op) continue;
      printf("%d\n", ans[i]);
    }
  }  
  return 0;
}