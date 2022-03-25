#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
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
const int maxn = 2000 + 5;

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    ll ans = 0;
    map<int,int> mp; mp[a[1]]++;
    for (int i = 2; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        int tag = 2 * a[i] - a[j];
        if (mp.count(tag)) ans += mp[tag];
      }
      mp[a[i]]++;
    }
    printf("%I64d\n", ans);
  }
  return 0;
}