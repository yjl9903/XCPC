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
const int maxn = 100000 + 5;

int n, a[maxn], b[maxn];
ll pre[maxn], suf[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pre[i] = a[i] + pre[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  for (int i = n; i >= 1; i--) {
    suf[i] = suf[i + 1];
    if (!b[i]) suf[i] += a[i];
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!b[i]) continue;
    ans += pre[i - 1] * a[i];
    ans += suf[i + 1] * a[i];
  }
  for (int i = 1; i < n; i++) {
    if (!b[i] && !b[i + 1]) {
      ans += a[i] * a[i + 1];
    }
  }
  if (!b[1] && !b[n]) ans += a[1] * a[n];
  cout << ans;
  return 0;
}