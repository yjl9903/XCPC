#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
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

int n;
PII a[maxn];

int get(int x) {
    int l = 0, r = 1000, ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (m * (m + 1) / 2 < x) ans = m + 1, l = m + 1;
        else r = m - 1;
    }
    dbg(x, ans);
    return ans;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ll ans = 0, suf = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].second, &a[i].first);
            a[i].second = get(a[i].second);
            suf += a[i].first;
        }
        sort(a + 1, a + 1 + n, [&](PII a, PII b) {
            return 1ll * a.first * b.second > 1ll * a.second * b.first;
        });
        for (int i = 1; i <= n; i++) {
            ans += suf * a[i].second;
            suf -= a[i].first;
        }
        printf("Case #%d: %lld\n", ++kase, ans);
    }
    return 0;
}