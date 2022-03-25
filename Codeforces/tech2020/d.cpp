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

int n, tot, tin[maxn], tout[maxn], rid[maxn], vis[maxn], deg[maxn];
vector<int> edge[maxn];

int query(int x, int y) {
  cout << "? " << x << ' ' << y << endl;
  cin >> x; assert(x >= 1 && x <= n);
  return x;
}

int ok[maxn];
void dfs(int u, int f) {
  tin[u] = ++tot; rid[tot] = u;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
  }
  tout[u] = tot;
}

bool check(int x, int y) {
  return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int main() {
  scanf("%d", &n);
  ok[1] = true;
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    ok[i] = true;
    edge[u].push_back(v);
    edge[v].push_back(u);
    deg[u]++; deg[v]++;
  }
  dfs(1, 0);
  vector<int> v;
  for (int i = 1; i <= n; i++) if (deg[i] == 1) v.push_back(i);
  assert(v.size() >= 2);
  for (int i = 1; i < (int)v.size(); i += 2) {
    int ans = query(v[i - 1], v[i]);
    for (int y: edge[ans]) {
      if (check(ans, y)) {
        if (check(y, v[i - 1]) || check(y, v[i])) {
          for (int j = tin[y]; j <= tout[y]; j++) {
            ok[rid[j]] = false;
          }
        }
      } else {
        if (!check(ans, v[i - 1]) || !check(ans, v[i])) {
          for (int j = 1; j < tin[ans]; j++) {
            ok[rid[j]] = false;
          }
          for (int j = tout[ans] + 1; j <= n; j++) {
            ok[rid[j]] = false;
          }
        }
      }
    }
  }
  v.clear();
  for (int i = 1; i <= n; i++) {
    if (!ok[i]) continue;
    int c = 0;
    for (int v: edge[i]) {
      if (ok[v]) c++;
    }
    assert(c <= 2);
    if (c == 1) {
      v.push_back(i);
    }
  }
  if (v.size() == 0) {
    for (int i = 1; i <= n; i++) {
      if (ok[i]) {
        cout << "! " << i << endl;
        return 0;
      }
    }
  } else if (v.size() == 2) {
    int r = query(v[0], v[1]);
    cout << "! " << r << endl;
  } else {
    assert(false);
  }
  return 0;
}