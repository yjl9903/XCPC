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

int n, pre[maxn], siz[maxn], p[maxn], c[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return ;
  pre[x] = y; siz[y] += siz[x];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      pre[i] = i; siz[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", p + i);
      join(i, p[i]);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", c + i);
    }
    int ans = n;
    for (int i = 1; i <= n; i++) {
      if (i != find(i)) continue;
      vector<int> v;
      int x = i;
      do {
        v.push_back(x);
        x = p[x];
      } while (x != i);
      int len = v.size();
      auto check = [&](int p) {
        for (int i = 0; i < p; i++) {
          bool flag = true;
          for (int j = i; j < len; j += p) {
            if (c[v[j]] != c[v[i]]) {
              flag = false; break;
            }
          }
          if (flag) {
            ans = min(ans, p);
            return ;
          }
        }
      };
      for (int k = 1; 1ll * k * k <= len; k++) {
        if (len % k) continue;
        check(k);
        check(len / k);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}