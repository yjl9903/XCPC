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
const int maxn = 1000 + 5;

int n, m, val[maxn];
bool vis[maxn], ok[maxn];
vector<int> edge[maxn];
set<int> bag[maxn];

bool in[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    int k;
    scanf("%d%d", val + i + m, &k);
    while (k--) {
      int x;
      scanf("%d", &x);
      edge[x].push_back(i + m);
    }
  }
  for (int i = 1; i <= n; i++) {
    int k;
    scanf("%d", &k);
    while (k--) {
      int x;
      scanf("%d", &x);
      edge[x + m].push_back(i + m);
    }
  }
  for (int i = 1; i <= m; i++) {
    ms(in, 0);
    function<void(int)> dfs = [&](int u) {
      in[u] = true;
      if (u > m) {
        bag[u].insert(i);
      }
      for (int v: edge[u]) {
        if (in[v]) continue;
        dfs(v);
      }
    };
    dfs(i);
  }
  set<int> cur;
  for (int i = m + 1; i <= m + n; i++) {
    cur.insert(i);
    for (int x: bag[i]) {
      vis[x] = true;
    }
  }
  int pos = 0, ans = 0;
  auto move = [&](int x) {
    printf("%d\n", -x);
    fflush(stdout);
    pos += x;
    scanf("%d", &x);
    return x;
  };
  auto update = [&](int x) {
    vector<int> vec;
    for (int u: cur) {
      if (bag[u].count(x)) {
        bag[u].erase(x);
      }
      if (bag[u].empty()) {
        ans += val[u];
        vec.push_back(u);
      }
    }
    for (int u: vec) {
      cur.erase(u);
    }
  };
  auto remove = [&](int x) {
    vector<int> vec;
    for (int u: cur) {
      if (bag[u].count(x)) {
        vec.push_back(u);
        continue;
      }
    }
    for (int u: vec) {
      cur.erase(u);
    }
  };
  auto need = [&](int x) -> bool {
    for (int u: cur) {
      if (bag[u].count(x)) {
        return true;
      }
    }
    return false;
  };
  while (pos + 1 <= m) {
    int x = 1;
    while (pos + x <= m && !need(pos + x)) x++;
    if (pos + x > m) break;
    int r = move(x);
    if (r) {
      update(pos);
    } else {
      remove(pos);
    }
  }
  printf("%d\n", ans);
  fflush(stdout);
  return 0;
}