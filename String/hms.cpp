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
const int maxn = 100000 + 5;

namespace BIT {
  ll c[maxn], s[maxn];
  inline int lowbit(int i) { return i & -i; }
  inline void update(int i, int x) {
    ll y = 1ll * i * x;
    for (; i < maxn; i += lowbit(i)) {
      c[i] += x; s[i] += y;
    }
  }
  inline void update(int l, int r, int x) {
    l++; r++;
    update(l, x); update(r + 1, -x);
  }
  inline ll query(ll* a, int i) {
    ll r = 0;
    for (; i; i -= lowbit(i)) r += a[i];
    return r;
  }
  inline ll query(int l, int r) {
    l++; r++;
    return (r - l + 1) * query(c, l - 1) + (r + 1) * (query(c, r) - query(c, l - 1)) 
      - query(s, r) + query(s, l - 1);
  }
}

namespace sam {
  int sz, last, cnt[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
  void clear() {
    for (int i = 1; i <= sz; i++) {
      len[i] = link[i] = cnt[i] = 0;
      ms(ch[i], 0);
    }
    sz = last = 1;
  }
  int insert(int c) {
    int cur = ++sz, p = last;
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int nq = ++sz;
        len[nq] = len[p] + 1;
        link[nq] = link[q];
        link[q] = link[cur] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
      }
    }
    return last = cur;
  }
  int tin[maxn << 1], tout[maxn << 1];
  vector<int> edge[maxn << 1];
  void build() {
    for (int i = 2; i <= sz; i++) {
      edge[link[i]].push_back(i);
    }
    int tot = 0;
    function<void(int)> dfs = [&](int u) {
      tin[u] = ++tot;
      for (int v: edge[u]) dfs(v);
      tout[u] = tot;
    };
    dfs(1);
  }
}
using sam::len;
using sam::tin;
using sam::tout;

int vis[maxn << 1], up[maxn << 1];
namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  int mx[maxn << 3];
  void update(int i, int x, int l = 1, int r = sam::sz, int rt = 1) {
    if (l == r) {
      mx[rt] = x; return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
  }
  int query(int L, int R, int l = 1, int r = sam::sz, int rt = 1) {
    if (L <= l && r <= R) return mx[rt];
    int m = (l + r) / 2, ans = 0;
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
  }
}

int n, q;
char s[maxn];
vector<PII> que[maxn];
ll ans[maxn];

int main() {
  sam::clear();
  scanf("%d%d%s", &n, &q, s + 1);
  for (int i = 1; i <= n; i++) {
    sam::insert(s[i] - 'a');
  }
  sam::build();
  for (int i = 1, l, r; i <= q; i++) {
    scanf("%d%d", &l, &r); l++; r++;
    que[r].emplace_back(l, i);
  }
  for (int r = 1, u = 1; r <= n; r++) {
    u = sam::ch[u][s[r] - 'a'];
    assert(sam::len[u] == r);
    BIT::update(1, r, 1);
    int x = u;
    while (x > 1 && !vis[x]) {
      vis[x] = true; x = sam::link[x];
    }
    dbg(r);
    while (x > 1) {
      int cur = SegT::query(tin[x], tout[x]);
      dbg(cur, len[x], up[cur], len[up[cur]]);
      BIT::update(cur - len[x] + 1, cur - len[up[cur]], -1);
      swap(up[cur], x);
    }
    SegT::update(tin[u], r); up[r] = 1;
    for (auto& q: que[r]) {
      ans[q.second] = BIT::query(q.first, r);
    }
  }
  for (int i = 1; i <= q; i++) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}