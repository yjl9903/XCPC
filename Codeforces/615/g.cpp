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
  #define dbg(args...) cout << "" << #args << " -> ", err(args)
  void err() { std::cout << "" << std::endl; }
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
const ll inf = 1ll << 60;
const int maxn = 500000 + 5;

int n, k;
int tin[maxn], cnt[maxn], tot;
bool key[maxn];
ll ans[maxn];
vector<PII> edge[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  ll mx[maxn << 2], tag[maxn << 2];
  void upd(int rt, ll x) {
    mx[rt] += x; tag[rt] += x;
  }
  void pushdown(int rt) {
    if (!tag[rt]) return ;
    upd(rt << 1, tag[rt]); upd(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }
  void update(int L, int R, ll x, int l = 1, int r = n + 1, int rt = 1) {
    if (L > R) return ;
    if (L <= l && r <= R) {
      upd(rt, x); return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
  }
}

ll sum = 0;
void predfs(int u, int f, int d) {
  tin[u] = key[u] ? ++tot : tot + 1;
  cnt[u] = key[u];
  if (key[u]) SegT::update(tin[u], tin[u], d);
  for (auto x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    predfs(v, u, d + x.second);
    cnt[u] += cnt[v];
    if (cnt[v]) sum += x.second;
  }
}

void dfs(int u, int f) {
  ans[u] = 2 * sum - SegT::mx[1];
  for (auto x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    if (cnt[v] == 0) sum += x.second;
    if (cnt[v] == k) sum -= x.second;
    SegT::update(tin[v], tin[v] + cnt[v] - 1, -2 * x.second);
    SegT::update(1, k, x.second);
    dfs(v, u);
    if (tin[v]) SegT::update(tin[v], tin[v] + cnt[v] - 1, 2 * x.second);
    SegT::update(1, k, -x.second);
    if (cnt[v] == 0) sum -= x.second;
    if (cnt[v] == k) sum += x.second;
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 2, u, v, w; i <= n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    edge[u].emplace_back(v, w);
    edge[v].emplace_back(u, w);
  }
  for (int i = 1, x; i <= k; i++) {
    scanf("%d", &x); key[x] = 1;
  }
  predfs(1, 0, 0); dfs(1, 0);
  for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
  return 0;
}