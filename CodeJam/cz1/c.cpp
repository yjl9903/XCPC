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
const int maxn = 1000000 + 5;

int n, a[maxn], b[maxn];

int main() {
  scanf("%d", &n);
  map<int,int> mp;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", a + i, b + i);
    mp[a[i]]++;
    if (a[i] != (a[i] ^ b[i])) {
      mp[a[i] ^ b[i]]++;
    }
  }
  int ans = mp.begin()->first, res = mp.begin()->second;
  for (auto& x: mp) if (x.second > res) ans = x.first, res = x.second;
  cout << ans << endl;
  return 0;
}