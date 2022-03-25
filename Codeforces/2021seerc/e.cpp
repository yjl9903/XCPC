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
const int maxn = 500000 + 5;

int n, a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }

  // int res = 0;
  // for (int i = 1; i <= n; i++) {
  //   int c1 = 0, c2 = 0;
  //   for (int j = i; j <= n; j++) {
  //     if (a[j] % 3 == 1) c1++;
  //     if (a[j] % 3 == 2) c2++;
  //     int cur = c1 * (c1 - 1) / 2 + c2 * (c2 - 1) + 2 * c1 * c2;
  //     if ((cur % 3 + 3) % 3 == 0) {
  //       dbg(i, j);
  //       res++;
  //     }
  //   }
  // }
  // dbg(res);

  int cnt1 = 0, cnt2 = 0;
  ll ans = 0;
  map<PII,int> mp;
  
  mp[{ 0, 0 }] = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i] % 3 == 1) cnt1++;
    if (a[i] % 3 == 2) cnt2++;
    cnt1 %= 3;
    cnt2 %= 3;
    dbg(i);
    for (int x = 0; x <= 2; x++) {
      for (int y = 0; y <= 2; y++) {
        int c1 = (cnt1 - x + 3) % 3;
        int c2 = (cnt2 - y + 3) % 3;
        int cur = c1 * (c1 - 1) / 2 + c2 * (c2 - 1) / 2 + 2 * c1 * c2;
        if ((cur % 3 + 3) % 3 == 0) {
          if (mp[{x,y}]) {
            dbg(x, y, mp[{ x, y }]);
            ans += mp[{ x, y }];
          }
        }
      }
    }
    mp[{ cnt1, cnt2 }]++;
  }
  cout << ans << endl;
  return 0;
}