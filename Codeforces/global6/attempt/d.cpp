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
#include <queue>
#include <random>
#include <ctime>
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
const int maxn = 100000 + 5;

int n, m, vis[maxn];
map<int,ll> ind[maxn], oud[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v, d; scanf("%d%d%d", &u, &v, &d);
    oud[u][v] += d;
    ind[v][u] += d;
  }
  auto ext = [&](int a, int b, int c) {
    ll w1 = ind[b][a], w2 = oud[b][c];
    if (w1 <= w2) {
      ind[b].erase(a);
      oud[a].erase(b);
      oud[b][c] -= w1;
      ind[c][b] -= w1;
      if (!oud[b][c]) {
        oud[b].erase(c);
        ind[c].erase(b);
      }
      oud[a][c] += w1;
      ind[c][a] += w1;
    } else {
      ind[c].erase(b);
      oud[b].erase(c);
      oud[a][b] -= w2;
      ind[b][a] -= w2;
      if (!oud[a][b]) {
        oud[a].erase(b);
        ind[b].erase(a);
      }
      oud[a][c] += w2;
      ind[c][a] += w2;
    }
  };
  vector<int> p; 
  for (int i = 1; i <= n; i++) p.push_back(i);
  // mt19937 rnd(time(0));
  // shuffle(begin(p), end(p), rnd);
  sort(begin(p), end(p), [&](int a, int b) {
    return ind[a].size() > ind[b].size();
  });
  for (int i = 1; i <= n; i++) {
    int u = p[i - 1];
    vector<pair<int,ll> > in, ou;
    for (auto& x: ind[u]) in.push_back(x);
    for (auto& x: oud[u]) ou.push_back(x);
    auto cmp = [](pair<int,ll> a, pair<int,ll> b) {
      return a.second > b.second;
    };
    sort(begin(in), end(in));
    sort(begin(ou), end(ou));
    int p1 = 0, p2 = 0;
    while (p1 < (int)in.size() && p2 < (int)ou.size()) {
      ext(in[p1].first, u, ou[p2].first);
      if (!ind[u].count(in[p1].first)) p1++;
      if (!oud[u].count(ou[p2].first)) p2++;
    }
  }
  vector<tuple<int,int,ll> > ans;
  for (int i = 1; i <= n; i++) {
    for (auto& x: oud[i]) ans.emplace_back(i, x.first, x.second);
  }
  printf("%d\n", ans.size());
  for (auto& x: ans) {
    int a, b; ll c;
    tie(a, b, c) = x;
    printf("%d %d %I64d\n", a, b, c);
  }
  return 0;
}