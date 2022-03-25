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

int n, a[maxn], pre[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= n + n; i++) {
      scanf("%d", a + i);
      pre[i] = 0;
      if (a[i] == 1) s1++;
      else if (a[i] == 2) s2++;
    }
    map<int,int> mp;
    mp[0] = 0;
    for (int i = n; i >= 1; i--) {
      if (i < n) pre[i] = pre[i + 1];
      if (a[i] == 1) pre[i]++;
      else pre[i]--;
      if (!mp.count(-pre[i])) mp[-pre[i]] = n - i + 1;
    }
    int ans = 2 * n, last = 0;
    if (mp.count(s2 - s1)) ans = mp[s2 - s1];
    for (int i = n + 1; i <= n + n; i++) {
      if (a[i] == 1) last++;
      else last--;
      // dbg(i, last, last + s2 - s1);
      if (mp.count(last + s2 - s1)) {
        // dbg(i, mp[last + s2 - s1]);
        ans = min(ans, mp[last + s2 - s1] + i - n);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}