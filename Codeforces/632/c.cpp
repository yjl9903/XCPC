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
  map<ll,int> mp; mp[0] = 0;
  ll ans = 0; int le = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%I64d", a + i);
    a[i] += a[i - 1];
    if (mp.count(a[i])) {
      le = max(le, mp[a[i]] + 1);
    }
    ans += i - le;
    mp[a[i]] = i;
  }
  cout << ans << endl;
  return 0;
}