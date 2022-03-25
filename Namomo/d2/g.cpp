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
using PDD = pair<double,double>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;
const double eps = 1e-3;

bool le(long double x, long double y) {
  if (abs(x - y) < eps) {
    return true;
  } else {
    return x < y;
  }
}

int n;
ll d, a[maxn];

int main() {
  scanf("%d%lld", &n, &d);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
  }
  
  return 0;
}