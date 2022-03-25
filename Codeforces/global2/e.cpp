#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
const int maxn = 300000 + 5;

int n, a[maxn];
ll mp[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    ll ans = a[0] / 3, cnt = a[0] % 3;
    for (int i = 1; i < n; i++) {
        ll tot = min(a[i] / 2ll, cnt);
        ans += tot;
        cnt -= tot;
        a[i] -= 2 * tot;
        ans += a[i] / 3; cnt += a[i] % 3;
    }
    cout << ans << endl;
    return 0;
}