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

int n, k, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    map<int,int> mp;
    vector<PII> evs;
    vector<int> le, ri;
    for (int i = 1; i <= n / 2; i++) {
      mp[a[i] + a[n - i + 1]]++;
      le.push_back(min(a[i], a[n - i + 1]) + 1);
      ri.push_back(max(a[i], a[n - i + 1]) + k);
      // dbg(min(a[i], a[n - i + 1]) + 1, max(a[i], a[n - i + 1]) + k);
      evs.emplace_back(min(a[i], a[n - i + 1]) + 1, 1);
      evs.emplace_back(max(a[i], a[n - i + 1]) + k + 1, -1);
    }
    sort(begin(evs), end(evs));
    sort(begin(le), end(le));
    sort(begin(ri), end(ri));
    int sum = 0, ans = n - 2;
    for (int i = 1; i <= n / 2; i++) {
      int x = a[i] + a[n - i + 1];
      int cnt = lower_bound(begin(ri), end(ri), x) - begin(ri);
      cnt += end(le) - upper_bound(begin(le), end(le), x);
      int tot = cnt * 2 + (n / 2 - cnt - mp[x]);
      ans = min(ans, tot);
    }
    for (auto& ev: evs) {
      if (ev.second > 0) {
        sum++;
        int tot = n - sum * 2 + sum;
        ans = min(ans, tot);
      } else {
        sum--;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}