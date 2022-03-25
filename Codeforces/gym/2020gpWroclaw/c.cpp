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

int n, deg[maxn];
vector<int> edge[maxn];

vector<int> onring;
int fa[maxn], ring[maxn], vis[maxn];
void getring(int u, int f) {
  vis[u] = 1;
  for (int v: edge[u]) {
    if (v == f) {
      f = -1;
      continue;
    }
    if (vis[v]) {
      if (!onring.empty()) continue;
      int x = u;
      while (x != v) {
        dbg(x);
        onring.push_back(x);
        x = fa[x];
      }
      onring.push_back(v);
    }
    fa[v] = u;
    getring(v, u);
  }
  vis[u] = 0;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      deg[i] = 0;
      fa[i] = 0;
      ring[i] = 0;
      vis[i] = 0;
      edge[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      deg[u]++;
      deg[v]++;
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (deg[i] == 1) {
        cnt++;
      }
    }
    if (cnt == 0) {
      puts("3");
    } else {
      onring.clear();
      getring(1, 0);
      assert(onring.size() >= 3);
      int ans = 0;
      bool flag = false;
      for (int i = 0; i < onring.size(); i++) {
        int x = onring[i];
        dbg(x, deg[x]);
        if (deg[x] == 2) {
          ans++;
          if (i > 0) {
            int y = onring[i - 1];
            if (deg[y] == 2) {
              flag = true;
            }
          } else {
            int y = onring.back();
            if (deg[y] == 2) {
              flag = true;
            }
          }
        }
      }
      dbg(ans, flag, cnt);
      if (ans == 0) {
        printf("%d\n", cnt);
      } else if (ans == 1) {
        printf("%d\n", cnt + 1);
      } else {
        if (flag) {
          printf("%d\n", cnt + 2);
        } else {
          printf("%d\n", cnt + 1);
        }
      }
    }
  }
  return 0;
}