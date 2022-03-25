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
using PII = pair<ll,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], b[maxn];

double cal(int a[]) {
  vector<PII> stk;
  for (int i = 1; i <= n; i++) {
    ll sum = a[i];
    int cnt = 1;
    while (!stk.empty() && stk.back().first * cnt > sum * stk.back().second) {
      sum += stk.back().first;
      cnt += stk.back().second;
      stk.pop_back();
    }
    stk.push_back({ sum, cnt });
  }
  double ans = 0;
  int i = 0;
  for (auto x: stk) {
    double avg = 1.0 * x.first / x.second;
    while (x.second--) {
      i++;
      ans += (avg - a[i]) * (avg - a[i]);
    }
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", a + i, b + i);
  }
  printf("%.8lf\n", cal(a) + cal(b));
  return 0;
}