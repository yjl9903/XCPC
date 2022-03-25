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

int n;
ll a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%I64d", a + i);
  }
  if (n == 1) {
    puts("1 1");
    printf("%d\n", -a[1]);
    puts("1 1");
    puts("0");
    puts("1 1");
    puts("0");
    return 0;
  }
  printf("1 1\n%d\n", -a[1]);
  a[1] = 0;
  printf("2 %d\n", n);
  for (int i = 2; i <= n; i++) {
    printf("%I64d ", 1ll * (a[i] % n) * (n - 1));
    a[i] += 1ll * (n - 1) * (a[i] % n);
  }
  puts("");
  printf("1 %d\n", n);
  for (int i = 1; i <= n; i++) {
    assert(a[i] % n == 0);
    printf("%I64d ", -a[i]);
  }
  return 0;
}