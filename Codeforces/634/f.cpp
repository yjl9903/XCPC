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
const int maxn = 2000000 + 5;

int n, m, fa[maxn];
bool key[maxn], ok[maxn], vis[maxn], ring[maxn], isB[maxn];
char s[maxn];
vector<int> edge[maxn];

int get(int x, int y) {
  return x * m + y;
}

vector<int> pos;
void dfs(int u, int f) {
  vis[u] = ok[u] = true;
  bool flag = true;
  for (int v: edge[u]) {
    if (v == f && flag) {
      flag = false;
      continue;
    }
    if (vis[v]) {
      if (!pos.empty()) continue;
      ring[v] = true;
      pos.push_back(v);
      int x = u;
      while (x != v) {
        ring[x] = true;
        pos.push_back(x);
        x = fa[x];
      }
      continue;
    }
    fa[v] = u; dfs(v, u);
  }
  vis[u] = 0;
}

int rlen;
int norm(int x) {
  return ((x % rlen) + rlen) % rlen;
}
void dfsR(int u, int f, int d) {
  isB[norm(d)] |= key[u];
  for (int v: edge[u]) {
    if (v == f) continue;
    if (ring[v] && ring[u]) continue;
    dfsR(v, u, d - 1);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      scanf("%s", s);
      for (int j = 0; j < m; j++) {
        key[get(i, j)] = !(s[j] - '0');
      }
    }
    set<PII> mp;
    for (int i = 0; i < n; i++) {
      scanf("%s", s);
      for (int j = 0; j < m; j++) {
        int u = get(i, j), v = 0;
        if (s[j] == 'U') {
          v = get(i - 1, j);
        } else if (s[j] == 'D') {
          v = get(i + 1, j);
        } else if (s[j] == 'L') {
          v = get(i, j - 1);
        } else if (s[j] == 'R') {
          v = get(i, j + 1);
        } else {
          assert(false);
        }
        mp.insert({ u, v });
        edge[u].push_back(v);
        edge[v].push_back(u);
      }
    }
    int ans = 0, ansB = 0;
    for (int i = 0; i < n * m; i++) {
      if (ok[i]) continue;
      pos.clear(); dfs(i, -1);
      if (!mp.count({ pos[0], pos[1] })) {
        reverse(begin(pos), end(pos));
      }
      rlen = pos.size();
      assert(rlen >= 2);
      for (int i = 0; i < rlen; i++) isB[i] = false;
      for (int i = 0; i < rlen; i++) {
        dfsR(pos[i], -1, i);
      }
      ans += rlen;
      for (int i = 0; i < rlen; i++) ansB += isB[i];
    }
    printf("%d %d\n", ans, ansB);
    for (int i = 0; i < n * m; i++) {
      vis[i] = ring[i] = fa[i] = ok[i] = 0;
      edge[i].clear();
    }
  }
  return 0;
}