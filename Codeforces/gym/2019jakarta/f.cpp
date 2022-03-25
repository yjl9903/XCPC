#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <map>
#include <cassert>
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
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace sieve{
  const int maxp = 2000000 + 5;
  int vis[maxp], prime[maxp], tot;
  void init() {
    for (int i = 2; i < maxp; i++) {
      if (!vis[i]) prime[++tot] = i;
      for (int j = 1; j <= tot && prime[j] * i < maxp; j++) {
        vis[i * prime[j]] = 1;
        if (i % prime[j] == 0) break;
      }
    }
  }
}
using sieve::prime;

int n, siz[maxn];
vector<int> edge[maxn];

ull val[maxn];
ull pack(ull val, int sz) {
  return 2ull + 3ull * val + 7ull * prime[sz + 1];
}
void geth(int u, int f, int cant) {
  siz[u] = 1; val[u] = 1;
  for (int v: edge[u]) {
    if (v == f || v == cant) continue;
    geth(v, u, cant);
    siz[u] += siz[v];
    val[u] += val[v] * prime[siz[v]];
  }
  val[u] = pack(val[u], siz[u]);
}

void getsz(int u, int f) {
  siz[u] = 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    getsz(v, u);
    siz[u] += siz[v];
  }
}
vector<int> rts;
int mn = inf, sum;
void getrt(int u, int f, int cant = -1) {
  siz[u] = 1;
  int mx = 0;
  for (int v: edge[u]) {
    if (v == f || v == cant) continue;
    getrt(v, u, cant); siz[u] += siz[v];
    mx = max(siz[v], mx);
  }
  mx = max(sum - siz[u], mx);
  if (mx == mn) rts.push_back(u);
  else if (mx < mn) {
    mn = mx; rts.clear();
    rts.push_back(u);
  }
}

int main() {
  sieve::init();
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  int ans = -1;
  sum = n; mn = inf;
  getrt(1, 0);
  assert((int)rts.size() <= 2);
  vector<int> rtss(rts);
  for (int rt: rtss) {
    getsz(rt, 0);
    bool first = 1;
    map<ull,int> mp;
    for (int v: edge[rt]) {
      sum = siz[v]; mn = inf;
      getrt(v, 0, rt);
      assert((int)rts.size() <= 2);
      map<ull,int> tmp;
      for (int srt: rts) {
        geth(srt, 0, rt);
        tmp[val[srt]] = 1;
      }
      for (auto& x: tmp) mp[x.first]++;
    }
    for (auto& x: mp) 
      if (x.second == (int)edge[rt].size()) 
        ans = max(ans, (int)edge[rt].size());
  }
  cout << ans;
  return 0;
}