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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n;
char s[maxn];

namespace SegTrees {
  const int maxm = maxn * 60;
  int tot, root[maxn << 1], ls[maxm], rs[maxm], val[maxm];
  void clear(int n) {
    tot = 0;
    for (int i = 0; i <= 2 * n; i++) root[i] = 0;
  }
  void update(int i, int l, int r, int& rt) {
    if (!rt) rt = ++tot, ls[rt] = rs[rt] = val[rt] = 0;
    if (l == r) {
      val[rt]++; return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, l, m, ls[rt]);
    else update(i, m + 1, r, rs[rt]);
    val[rt] = val[ls[rt]] + val[rs[rt]];
  }
  int join(int x, int y, int l = 1, int r = n) {
    if (!x || !y) return x + y;
    int u = ++tot; ls[u] = rs[u] = val[u] = 0;
    if (l == r) {
      val[u] = val[x] + val[y];
    } else {
      int m = (l + r) / 2;
      ls[u] = join(ls[x], ls[y], l, m);
      rs[u] = join(rs[x], rs[y], m + 1, r);
      val[u] = val[ls[u]] + val[rs[u]];
    }
    return u;
  }
  int query(int L, int R, int l, int r, int rt) {
    if (!rt) return 0;
    if (L <= l && r <= R) return val[rt];
    int m = (l + r) / 2, ans = 0;
    if (L <= m) ans = query(L, R, l, m, ls[rt]);
    if (R > m) ans += query(L, R, m + 1, r, rs[rt]);
    return ans;
  }
}
using SegTrees::root;

namespace sam {
  int sz, last, cnt[maxn << 1], pos[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
  void clear() {
    for (int i = 1; i <= sz; i++) {
      len[i] = link[i] = cnt[i] = 0;
      ms(ch[i], 0);
    }
    sz = last = 1;
  }
  int insert(int c, int i) {
    int cur = ++sz, p = last;
    len[cur] = len[last] + 1;
    cnt[cur] = 1; pos[cur] = i;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int nq = ++sz;
        pos[nq] = pos[q];
        len[nq] = len[p] + 1;
        link[nq] = link[q];
        link[q] = link[cur] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
      }
    }
    return last = cur;
  }

  vector<int> edge[maxn << 1];
  int top[maxn << 1], dp[maxn << 1];
  int solve() {
    for (int i = 2; i <= sz; i++) edge[link[i]].push_back(i);
    int ans = 1;
    function<void(int)> predfs = [&](int u) {
      for (int v: edge[u]) {
        predfs(v);
        root[u] = SegTrees::join(root[u], root[v]);
      }
    };
    function<void(int)> dfs = [&](int u) {
      if (u != 1) {
        if (link[u] == 1) {
          top[u] = u; dp[u] = 1;
        } else {
          int rt = top[link[u]];
          int l = pos[u] - len[u] + len[rt], r = pos[u] - 1;
          if (SegTrees::query(l, r, 1, n, root[rt])) {
            dp[u] = dp[rt] + 1; ans = max(ans, dp[u]);
            top[u] = u;
          } else {
            dp[u] = dp[rt];
            top[u] = rt;
          }
        }
      }
      for (int v: edge[u]) dfs(v);
    };
    predfs(1); dfs(1);
    return ans;
  }
}

int main() {
  scanf("%d%s", &n, s + 1);
  sam::clear(); SegTrees::clear(n);
  for (int i = 1; i <= n; i++) {
    int u = sam::insert(s[i] - 'a', i);
    SegTrees::update(i, 1, n, root[u]);
  }
  printf("%d\n", sam::solve());
  return 0;
}