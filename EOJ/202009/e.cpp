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

int cal(int x) {
  while (x >= 10) {
    int sum = 0;
    int y = x;
    while (y) {
      sum += y % 10;
      y /= 10;
    }
    x = sum;
  }
  return x;
}

int main() {
  scanf("%d", &n);
  int last = -1, flag = true;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    if (last == -1) {
      last = a[i];
    } else {
      if (last + 1 != a[i]) {
        flag = false;
      }
      last = a[i];
    }
    if (last == 9) {
      last = 0;
    }
  }
  if (flag) {
    printf("%d %d\n", a[1], a[1] + n - 1);
    for (int i = 0; i < n; i++) {
      dbg(a[i + 1], i + a[1], cal(i + a[1]));
      assert(a[i + 1] == cal(i + a[1]));
    }
  } else {
    puts("-1");
  }
  return 0;
}