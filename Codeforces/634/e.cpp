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

int n, a[maxn];
vector<int> bag[maxn];

int query(int c, int l, int r) {
  if (l > r) return 0;
  return upper_bound(begin(bag[c]), end(bag[c]), r) - lower_bound(begin(bag[c]), end(bag[c]), l);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= 200; i++) {
      bag[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      bag[a[i]].push_back(i);
    }
    int ans = 0;
    for (int i = 1; i <= 200; i++) {
      int len = (int)bag[i].size();
      ans = max(ans, len);
      if (len < 2) continue;
      for (int j = 0; j < len - 1 - j; j++) {
        int mx = 0, lp = bag[i][j], rp = bag[i][len - 1 - j];
        // dbg(i, j, len, lp, rp);
        for (int c = 1; c <= 200; c++) {
          mx = max(mx, query(c, lp + 1, rp - 1));
        }
        ans = max(ans, mx + j + j + 2);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}