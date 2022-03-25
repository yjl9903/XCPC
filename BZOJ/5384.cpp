#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, m, node[maxn], tin[maxn], tout[maxn], tot;
char s[maxn];
vector<int> edge[maxn];
vector<PII> que[maxn];

void dfs(int u) {
  tin[u] = ++tot;
  for (int i = 0; i < (int)edge[u].size(); i++) {
    dfs(edge[u][i]);
  }
  tout[u] = tot;
}

namespace pam {
  int sz, tot, last;
  int ch[maxn][26], len[maxn], fail[maxn];
  int cnt[maxn], dep[maxn], dif[maxn], slink[maxn];
  char s[maxn];
  int node(int l) {
    sz++; ms(ch[sz], 0);
    len[sz] = l; fail[sz] = 0;
    cnt[sz] = dep[sz] = 0;
    return sz;
  }
  void clear() {
    sz = -1; last = 0;
    s[tot = 0] = '$';
    node(0); node(-1);
    fail[0] = 1;
  }
  int getfail(int x) {
    while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
    return x;
  }
  int insert(char c) {
    s[++tot] = c;
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
      int x = node(len[now] + 2);
      fail[x] = ch[getfail(fail[now])][c - 'a'];
      dep[x] = dep[fail[x]] + 1;
      ch[now][c - 'a'] = x;
 
      dif[x] = len[x] - len[fail[x]];
      if (dif[x] == dif[fail[x]]) slink[x] = slink[fail[x]];
      else slink[x] = fail[x];
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
    return last;
  }
}
using pam::len;
using pam::fail;
using pam::slink;
using pam::dif;

struct BIT {
  int a[maxn];
  void update(int i, int x) {
    for (; i <= n; i += i & -i) a[i] += x;
  }
  void update(int l, int r, int x) {
    update(l, x); update(r + 1, -x);
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
} f;
struct SegTree {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  int a[maxn << 2];
  void update(int i, int x, int l = 1, int r = pam::sz + 1, int rt = 1) {
    if (l == r) {
      a[rt] = x; return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }
  int query(int L, int R, int l = 1, int r = pam::sz + 1, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2, ans = 0;
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
  }
} g;

int main() {
  pam::clear();
  scanf("%d%d%s", &n, &m, s + 1);
  for (int i = 1; i <= n; i++) node[i] = pam::insert(s[i]);
  edge[1].push_back(0);
  for (int i = 2; i <= pam::sz; i++) edge[fail[i]].push_back(i);
  dfs(1);
  for (int i = 1, l, r; i <= m; i++) {
    scanf("%d%d", &l, &r); que[r].push_back({l, i});
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int u = node[i];
    for (int x = u; x > 1; x = slink[x]) {
      int pos = g.query(tin[x], tout[x]) - len[x] + 1;
      int l = max(pos + 1, 1);
      int r = i - len[slink[x]] - dif[x] + 1;
      f.update(l, r, 1);
    }
    g.update(tin[u], i);
    for (int j = 0; j < (int)que[i].size(); j++) {
      int p = que[i][j].first, id = que[i][j].second;
      dbg(p, i, f.query(p));
      ans += 1ll * id * f.query(p) % mod;
      if (ans >= mod) ans -= mod;
    }
  }
  printf("%d", ans);
  return 0;
}