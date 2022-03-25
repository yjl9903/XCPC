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
const int maxn = 200000 + 5;

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    ll sum = 0, sumx = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      sum += a[i];
      sumx ^= a[i];
    }
    if (sum == 2 * sumx) {
      puts("0"); puts("");
      continue;
    }
    vector<ll> plan;
    if (sum % 2 == 0) {
      if (sum > 2 * sumx) {
        plan.push_back(1ll << 50);
        sum += 1ll << 50;
        sumx ^= 1ll << 50;
      }
      // assert(sum < 2 * sumx);
      plan.push_back((2 * sumx - sum) / 2);
      plan.push_back((2 * sumx - sum) / 2);
    } else {
      plan.push_back((1ll << 50) + 1);
      sum += (1ll << 50) + 1;
      sumx ^= (1ll << 50) + 1;
      assert(sum < 2 * sumx);
      plan.push_back((2 * sumx - sum) / 2);
      plan.push_back((2 * sumx - sum) / 2);
    }
    printf("%d\n", plan.size());
    for (auto& x: plan) printf("%I64d ", x);
    puts("");
  }
  return 0;
}
