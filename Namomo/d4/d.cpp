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

int n, m, a[maxn], dep[maxn], dis[maxn];
char s[maxn], t[maxn];
vector<PII> edge[maxn];
vector<int> bag[maxn];

map<string, int> mp;
int gid(const string& s) {
  static int tot = 0;
  if (mp.count(s)) {
    return mp[s];
  } else {
    return mp[s] = ++tot;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    a[i] = gid(s);
    dep[i] = dis[i] = inf;
  }
  assert(gid("English") == n + 1);
  for (int i = 1; i <= m; i++) {
    int w;
    scanf("%s%s%d", s, t, &w);
    int u = gid(s);
    int v = gid(t);
    edge[u].emplace_back(v, w);
    edge[v].emplace_back(u, w);
  }
  queue<int> q;
  q.push(n + 1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto& x: edge[u]) {
      int v = x.first;
      if (dep[v] > dep[u] + 1) {
        dep[v] = dep[u] + 1;
        q.push(v);
      }
    }
  }
  for (int i = 1; i <= n + 1; i++) {
    dbg(i, dep[i]);
    if (dep[i] == inf) {
      puts("Impossible");
      return 0;
    } else {
      bag[dep[i]].push_back(i);
    }
  }
  ll ans = 0;
  for (int i = 0; i <= n; i++) {
    if (bag[i].empty()) break;
    for (int u: bag[i]) {
      ans += dis[u];
      for (auto& x: edge[u]) {
        int v = x.first;
        int w = x.second;
        if (dep[v] == i + 1) {
          dis[v] = min(dis[v], w);
        }
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}