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

struct E {
  int u, v, w;
} eg[maxn];

int m, v, e, s, t, a[maxn], b[maxn];

int main() {
  scanf("%d%d%d%d%d", &m, &v, &e, &s, &t);
  for (int i = 1; i <= e; i++) {
    scanf("%d%d%d", &eg[i].u, &eg[i].v, &eg[i].w);
  }
  a[s] = m;
  int tot = 0;
  while (true) {
    for (int i = 1; i <= v; i++) {
      b[i] = a[i];
    }
    for (int i = 1; i <= e; i++) {
      int u = eg[i].u, v = eg[i].v, w = eg[i].w;
      b[v] += min(w, a[u]);
    }
    for (int i = 1; i <= v; i++) {
      a[i] = min(m, max(b[i], a[i]));
    }
    tot++;
    if (a[t] >= m) {
      printf("%d\n", tot);
      break;
    }
  }
  return 0;
}