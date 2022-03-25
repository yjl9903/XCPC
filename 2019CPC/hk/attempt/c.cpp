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
typedef pair<int,ll> PIL;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], vis[maxn];
vector<int> edge[maxn];

int siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
  siz[u] = 1; int t = 0;
  for (int v: edge[u]) {
    if (v == f || vis[v]) continue;
    getrt(v, u); siz[u] += siz[v];
    t = max(t, siz[v]);
  }
  t = max(t, sum - siz[u]);
  if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
  sum = siz[u]; mn = 1e9; rt = 0;
  getrt(u, 0); return rt;
}

namespace BIT {
  int n, a[maxn * 4];
  void update(int i, int x) {
    i = n - i + 1;
    for (; i <= n; i += i & -i) a[i] += x;
  }
  int query(int i) {
    i = n - i + 1;
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
};

struct Query {
  int op, x, y;
  bool operator<(const Query& b) const {
    if (x == b.x) return op > b.op;
    return x < b.x;
  }
};

ll ans;
ll cal(vector<PIL>& vec, int val) {
  vector<ll> lsh;
  for (auto& x: vec) {
    lsh.push_back(x.second - val);
    lsh.push_back(2 * x.first - x.second + 1);
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  BIT::n = (int)lsh.size();
  auto gid = [&](ll x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };
  ll ans = 0;
  vector<Query> que;
  for (auto& x: vec) {
    que.push_back({ 0, x.first, gid(2 * x.first - x.second + 1) }); // qry
    que.push_back({ 1, x.first, gid(x.second - val) }); // upd
  }
  sort(begin(que), end(que));
  for (auto& q: que) {
    if (q.op == 0) {
      // ans += BIT::query(q.y) - 1;
      ans += BIT::query(q.y);
    } else if (q.op == 1) {
      BIT::update(q.y, 1);
    }
  }
  for (auto& q: que) {
    if (q.op == 1) {
      BIT::update(q.y, -1);
    }
  }
  // sort(begin(vec), end(vec));
  // for (int i = 0, j; i < (int)vec.size(); i = j) {
  //   vector<ll> v;
  //   j = i;
  //   while (j < (int)vec.size() && vec[j].first == vec[i].first) {
  //     v.push_back(2 * vec[j].first - vec[j].second); j++;
  //   }
  //   sort(begin(v), end(v));
  //   ll tmp = 0;
  //   for (int k = i; k < j; k++) {
  //     int rk = upper_bound(begin(v), end(v), vec[k].second) - begin(v);
  //     tmp += rk; 
  //   }
  //   dbg(vec[i].first, tmp);
  // }
  // dbg(ans);
  return ans;
}

void solve(int u) {
  dbg(u);
  vis[u] = 1;
  vector<PIL> vec; vec.push_back({ a[u], 1ll * a[u] });
  function<void(int,int,int,ll)> dfs = [&](int u, int f, int mx, ll sum) {
    mx = max(mx, a[u]); sum += a[u];
    vec.emplace_back(mx, sum);
    for (int v: edge[u]) {
      if (v == f || vis[v]) continue;
      dfs(v, u, mx, sum);
    }
  };
  for (int v: edge[u]) {
    if (vis[v]) continue;
    dfs(v, u, a[u], a[u]);
  }
  dbg("add");
  // ans += cal(vec, a[u]) + 1;
  ans += cal(vec, a[u]);

  for (int v: edge[u]) {
    if (vis[v]) continue;
    vec.clear();
    dfs(v, u, a[u], a[u]);
    dbg("sub", v);
    ans -= cal(vec, a[u]);
  }
  for (int v: edge[u]) {
    if (vis[v]) continue;
    solve(getrt(v));
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      edge[i].clear(); vis[i] = 0;
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    ans = 0; siz[1] = n; 
    solve(getrt(1));
    printf("%lld\n", ans);
  }
  return 0;
}