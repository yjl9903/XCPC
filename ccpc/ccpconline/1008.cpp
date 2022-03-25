#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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

int n, k, a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        ll ans = k, cnt = 0;
        for (int i = 1; i <= n; i++) ans += a[i], cnt += a[i] / k;
        for (int i = 1; i <= n; i++) a[i] = k - a[i] % k;
        for (int i = 1; i <= n; i++) dbg(a[i]);
        sort(a + 1, a + 1 + n);
        for (int i = 1; i <= n - cnt - 1; i++) ans += a[i];
        printf("%lld\n", ans);
    }
    return 0;
}