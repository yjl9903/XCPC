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

struct fastIO {
  char s[100000]; int it, len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, 100000, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  bool notend() {
    char c = get();
    while(c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;
inline int gi() {
  int r = 0; bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}

struct Edge {
  int to, nxt;
} g[maxn * 2];
int ecnt, head[maxn];
void adde(int u, int v) {
  g[++ecnt] = (Edge){ v, head[u] };
  head[u] = ecnt;
}

int n, a[maxn], vis[maxn];

int siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
  siz[u] = 1; int t = 0;
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
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
  sort(begin(vec), end(vec));
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
  for (auto& q: vec) {
    ans += BIT::query(gid(2 * q.first - q.second + 1));
    BIT::update(gid(q.second - val), 1);
  }
  for (auto& q: vec) {
    BIT::update(gid(q.second - val), -1);
  }
  return ans;
}

void solve(int u) {
  // dbg(u);
  vis[u] = 1;
  vector<PIL> vec; vec.push_back({ a[u], 1ll * a[u] });
  function<void(int,int,int,ll)> dfs = [&](int u, int f, int mx, ll sum) {
    siz[u] = 1;
    mx = max(mx, a[u]); sum += a[u];
    vec.emplace_back(mx, sum);
    for (int i = head[u]; i; i = g[i].nxt) {
      int v = g[i].to;
      if (v == f || vis[v]) continue;
      dfs(v, u, mx, sum); siz[u] += siz[v];
    }
  };
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (vis[v]) continue;
    dfs(v, u, a[u], a[u]);
  }
  ans += cal(vec, a[u]);

  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (vis[v]) continue;
    vec.clear();
    dfs(v, u, a[u], a[u]);
    ans -= cal(vec, a[u]);
  }
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (vis[v]) continue;
    solve(getrt(v));
  }
}

int main() {
  int T = gi();
  while (T--) {
    ecnt = 0;
    n = gi();
    for (int i = 1; i <= n; i++) {
      a[i] = gi();
      vis[i] = head[i] = 0;
    }
    for (int i = 2, u, v; i <= n; i++) {
      u = gi(); v = gi();
      adde(u, v); adde(v, u);
    }
    ans = 0; siz[1] = n; 
    solve(getrt(1));
    printf("%lld\n", ans);
  }
  return 0;
}