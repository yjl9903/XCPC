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
#include <bitset>
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
const int maxn = 100000 + 5;

int m, n, a[maxn], b[maxn], ord[maxn];
vector<int> bag[maxn];
bitset<10> has[maxn], vis;

int main() {
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
    ord[i] = i;
  }
  sort(ord + 1, ord + 1 + n, [&](int x, int y) {
    return b[x] < b[y];
  });
  for (int i = 1; i <= m; i++) {
    int k, x;
    scanf("%d", &k);
    while (k--) {
      scanf("%d", &x);
      has[i].set(x);
      bag[x].push_back(i);
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    vis.reset();
    int cur = ord[i];
    sort(begin(bag[cur]), end(bag[cur]), [&](int x, int y) {
      return a[x] > a[y];
    });
    for (int j: bag[cur]) {
      int cnt = (has[j] & vis).reset(cur).count();
      if (cnt > 0) {
        ans += b[cur] + a[j];
        has[j].reset(cur);
        dbg(j, cur);
      }
      vis |= has[j];
    }
  }
  printf("%I64d\n", ans);
  return 0;
}