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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, a[maxn], b[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  auto sub = [&](int x, int y) {
    x -= y; return x >= 0 ? x : x + m;
  };
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + n);
  int ans = m + 1;
  for (int i = 0; i < n; i++) {
    int d = sub(b[i + 1], a[1]);
    int flag = 1;
    dbg(i);
    for (int j = 2; j <= n; j++) {
      dbg(j, (i + j - 1) % n + 1);
      if (sub(b[(i + j - 1) % n + 1], a[j]) != d) {
        flag = 0; break;
      }
    }
    if (flag) {
      ans = min(ans, d);
    }
  }
  printf("%d\n", ans);
  return 0;
}