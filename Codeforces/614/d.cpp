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
const int maxn = 200000 + 5;

int n, pos[maxn], w[maxn], divsor[maxn], dep[maxn];
vector<PII> edge[maxn];

struct BIT {
  int a[maxn];
  void add(int i, int x) {
    for (; i <= 5000; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
} h;

int main() {
  for (int i = 2; i < maxn; i++) {
    if (divsor[i]) continue;
    divsor[i] = i;
    for (int j = i + i; j < maxn; j += i) {
      if (!divsor[j]) {
        divsor[j] = i;
      }
    }
  }

  scanf("%d", &n);

  int cnt = 1;
  dep[1] = 0; pos[1] = 1;
  edge[1].clear();
  vector<int> stk { 1 };
  for (int i = 2; i <= 5000; i++) {
    map<int,int> mp;
    int x = i;
    while (x > 1) {
      mp[divsor[x]]++;
      x /= divsor[x];
    }
    int lcaDep = h.query(mp.rbegin()->first, 5000);
    for (auto& x: mp) {
      h.add(x.first, x.second);
    }

    if (dep[stk.back()] != lcaDep) {
      while (lcaDep < dep[stk[(int)stk.size() - 2]]) {
        PII e { stk.back(), dep[stk.back()] - dep[stk[(int)stk.size() - 2]] };
        edge[stk[(int)stk.size() - 2]].push_back(e);
        stk.pop_back();
      }
      if (lcaDep > dep[stk[(int)stk.size() - 2]]) {
        edge[++cnt].clear(); w[cnt] = 0;
        dep[cnt] = lcaDep;
        PII e { stk.back(), dep[stk.back()] - lcaDep };
        edge[cnt].push_back(e);
        stk.pop_back();
        stk.push_back(cnt);
      } else {
        PII e { stk.back(), dep[stk.back()] - dep[stk[(int)stk.size() - 2]] };
        edge[stk[(int)stk.size() - 2]].push_back(e);
        stk.pop_back();
      }
    }

    edge[++cnt].clear(); w[cnt] = 0;
    dep[cnt] = h.query(5000);
    stk.push_back(cnt);
    pos[i] = cnt;
  }
  for (int i = 0; i + 1 < (int)stk.size(); i++) {
    PII e { stk[i + 1], dep[stk[i + 1]] - dep[stk[i]] };
    edge[stk[i]].push_back(e);
  }
  
  ll ans = 0;
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    if (x == 0) x = 1;
    w[pos[x]]++;
    ans += dep[pos[x]];
  }
  function<void(int)> dfs = [&](int u) {
    for (auto x: edge[u]) {
      int v = x.first;
      dfs(v);
      w[u] += w[v];
    }
  };
  dfs(1);
  int u = 1;
  while (true) {
    bool ok = true;
    for (auto& x: edge[u]) {
      int v, d; tie(v, d) = x;
      if (w[1] - w[v] - w[v] < 0) {
        ok = false;
        u = v;
        ans += 1ll * d * (w[1] - w[v] - w[v]);
        break;
      }
    }
    if (ok) break;
  }
  printf("%lld\n", ans);
  return 0;
}