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
  sort(a + 2, a + n + 1, greater<ll>());
  vector<pair<ll,int> > b = { { a[2], 1 } };
  for (int i = 3; i <= n; i++) {
    if (a[i] == b.back().first) {
      b.back().second++;
    } else {
      b.push_back({ a[i], 1 });
    }
  }

  ll ans = 0;
  ll h = b.front().first;
  int cnt = b.front().second;
  for (int j = 1; j < b.size(); j++) {
    ll delta = h - (b[j].first + ans);
    int c = __lg(cnt) + 1;
    if (delta * (c - 1) > a[1] - h) {
      assert(c > 1);
      ll time = (a[1] - h) / (c - 1) * c;
      time += (a[1] - h) % (c - 1);
      printf("%I64d\n", ans + time);
      return 0;
    } else {
      ans += delta * c;
      h += delta * (c - 1);
      cnt += b[j].second;
    }
  }
  int c = __lg(cnt) + 1;
  ll time = (a[1] - h) / (c - 1) * c;
  time += (a[1] - h) % (c - 1);
  cout << ans + time << endl;
  return 0;
}