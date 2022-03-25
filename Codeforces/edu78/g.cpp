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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
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

int n, x, d;

int main() {
  cin >> n >> x >> d;
  if (d == 0) {
    if (x == 0) cout << 1 << endl;
    else cout << 1 + n << endl;
    return 0;
  } else if (d < 0) {
    d = -d, x = -x;
  }
  vector<tuple<ll,ll,ll> > all;
  for (int i = 0; i <= n; i++) {
    ll st = 1ll * i * (i - 1) / 2;
    ll ed = 1ll * i * (n - 1 + n - i) / 2;
    ll fi = 1ll * i * x;
    st += fi / d; ed += fi / d;
    all.emplace_back(fi % d, st, ed);
  }
  sort(begin(all), end(all));
  ll ans = 0;
  for (int i = 0, j; i <= n; i = j) {
    j = i;
    while (j <= n && get<0>(all[i]) == get<0>(all[j])) {
      j++;
    }
    for (int p = i, q; p < j; p = q) {
      q = p;
      ll ri = get<2>(all[p]);
      while (q < j && get<1>(all[q]) <= ri) {
        ri = max(ri, get<2>(all[q])); q++;
      }
      ans += ri - get<1>(all[p]) + 1;
    }
  }
  cout << ans << endl;
  return 0;
}