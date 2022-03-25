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

int n, a[maxn];

int main() {
  scanf("%d", &n);
  map<int,vector<int> > mp;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    int x = a[i];
    for (int j = 2; 1ll * j * j <= x; j++) {
      if (x % j) continue;
      int c = 0; while (x % j == 0) x /= j, c++;
      mp[j].push_back(c);
    }
    if (x > 1) {
      mp[x].push_back(1);
    }
  }
  ll ans = 1;
  for (auto& x: mp) {
    sort(begin(x.second), end(x.second));
    if (x.second.size() == n) {
      int c = x.second[1];
      while (c--) ans *= x.first;
    } else if (x.second.size() == n - 1) {
      int c = x.second[0];
      while (c--) ans *= x.first;
    }
  }
  cout << ans << endl;
  return 0;
}