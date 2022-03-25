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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, l, key[maxn], deg[maxn], val[maxn];
vector<int> edge[maxn], edge2[maxn];

void dfs(int u) {
  key[u] = 1;
  for (int v: edge[u]) {
    if (key[v]) continue;
    dfs(v);
  }
}

int main() {
  scanf("%d%d", &n, &l);
  for (int i = 1; i <= l; i++) {
    int k, x; scanf("%d", &k);
    for (int j = 1; j <= k; j++) {
      scanf("%d", &x);
      edge[i].push_back(x);
    }
  }
  dfs(1);
  for (int i = 1; i <= l; i++) {
    if (!key[i]) continue;
    for (int v: edge[i]) {
      if (!key[v]) continue;
      edge2[i].push_back(v);
      deg[v]++;
    }
  }
  assert(deg[1] == 0);
  queue<int> q; q.push(1);
  val[1] = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v: edge2[u]) {
      val[v] = add(val[u], val[v]);
      deg[v]--;
      if (!deg[v]) {
        q.push(v);
      }
    }
  }
  int ans = 0, cnt = 0;
  for (int i = l + 1; i <= n; i++) {
    if (!key[i]) continue;
    ans = add(ans, val[i]);
    cnt++;
  }
  printf("%d %d\n", ans, cnt);
  return 0;
}