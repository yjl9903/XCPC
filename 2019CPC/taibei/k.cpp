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
#include <queue>
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
const ll inf = 1ll << 60;
const int maxn = 1000 + 5;

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    priority_queue<ll, vector<ll>, greater<ll> > pq;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      pq.push(a[i]);
    }
    ll ans = 0;
    while (pq.size() > 1) {
      ll u = pq.top(); pq.pop();
      ll v = pq.top(); pq.pop();
      ans += u + v;
      pq.push(u + v);
    }
    printf("%lld\n", ans);
  }
  return 0;
}