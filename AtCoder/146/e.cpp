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
const int maxn = 600000 + 5;

int n, k, b[maxn];
ll ans, a[maxn];

int main() {
  scanf("%d%d", &n, &k);
  map<int,int> mp; mp[0] = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    a[i] += a[i - 1];
    b[i] = ((a[i] - i) % k + k) % k;
    if (i >= k) mp[b[i - k]]--;
    ans += mp[b[i]];
    mp[b[i]]++;
  }
  // (pre(r) - pre(l)) % k == r - l
  // pre(r) - pre(l) = x * k + r - l
  // pre(r) - r = pre(l) - l + x * k
  printf("%lld\n", ans);
  return 0;
}