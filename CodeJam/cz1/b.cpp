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

int n, a[maxn], ans[maxn];

int main() {
  scanf("%d", &n);
  vector<PII> vec;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    vec.emplace_back(a[i], i);
  }
  sort(begin(vec), end(vec));
  for (int i = 0; i < n; i++) {
    int pos = vec[i].second, val = a[pos];
    int tot = 0;
    if (pos > 1) {
      if (val == a[pos - 1]) {
        ans[pos] = ans[pos - 1];
        continue;
      }
      tot = ans[pos - 1];
    }
    if (pos < n) {
      tot = max(tot, ans[pos + 1]);
    }
    ans[pos] = tot + 1;
  }
  ll res = 0;
  for (int i = 1; i <= n; i++) {
    res += ans[i];
  }
  cout << res << endl;
  return 0;
}