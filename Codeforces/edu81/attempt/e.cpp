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
  #define dbg(args...) cout << #args << " -> ", err(args)
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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, p[maxn], a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", p + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  ll ans = 1e18;
  for (int i = 1; i <= n; i++) {
    dbg(i);
    ll mn = 1e18;
    for (int j = 1; j <= n - 1; j++) {
      ll sum = 0;
      for (int k = 1; k <= j; k++) {
        if (p[k] > i) sum += a[k];
      }
      for (int k = j + 1; k <= n; k++) {
        if (p[k] <= i) sum += a[k];
      }
      dbg(j, sum);
    }
  }
  return 0;
}