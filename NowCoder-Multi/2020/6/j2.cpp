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
const int maxn = 1000000 + 5;

int n, m, ans[maxn], trans[maxn], temp[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    ans[i] = i;
  }
  for (int i = 1, k, x; i <= m; i++) {
    scanf("%d%d", &k, &x);
    int cur = 0;
    auto next = [&](int cur) {
      if (cur == n) return 1;
      else return cur + 1;
    };
    vector<int> vis(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      int cnt = 0;
      while (cnt < k) {
        cur = next(cur);
        if (!vis[cur]) {
          cnt++;
        }
      }
      vis[cur] = 1;
      // dbg(cur);
      trans[i] = cur;
    }
    for (int _ = 0; _ < x; _++) {
      for (int i = 1; i <= n; i++) {
        temp[i] = trans[ans[i]];
      }
      for (int i = 1; i <= n; i++) {
        ans[i] = temp[i];
      }
    }
    // dbg("OK");
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", ans[i], " \n"[i == n]);
  }
  return 0;
}