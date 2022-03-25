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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

bool check(ll x) {
  vector<int> v;
  while (x > 0) {
    v.push_back(x % 10);
    x /= 10;
  }
  for (int i = 0; i < v.size(); i++) {
    int cur = 0;
    for (int j = i; j < v.size(); j++) {
      cur = (cur + v[j]) % 3;
      if (cur == 0) return true;
    }
  }
  return false;
}

int sum[maxn];

ll cal(ll x) {
  if (x <= 1000) {
    return sum[x];
  } else {
    return (x - 1000) + sum[1000];
  }
}

int main() {
  for (int i = 1; i <= 1000; i++) {
    sum[i] = sum[i - 1] + check(i);
  }
  int T; scanf("%d", &T);
  while (T--) {
    ll L, R;
    scanf("%lld%lld", &L, &R);
    printf("%lld\n", cal(R) - cal(L - 1));
  }
  return 0;
}