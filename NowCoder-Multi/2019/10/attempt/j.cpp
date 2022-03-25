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
typedef pair<int,ll> PIL;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5000 + 5;

int n, k;
PIL a[maxn];

ll dp[maxn][maxn], mx[maxn], suf[maxn], opt[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%d", &a[i].second, &a[i].first);
    }
    sort(a + 1, a + 1 + n);
    int cnt = 0;
    for (int i = 1, j; i <= n; i = j) {
        j = i;
        ll sum = 0;
        while (j <= n && a[j].first == a[i].first) {
            sum += a[j].second; j++;
        }
        a[++cnt] = { a[i].first, sum };
    }
    n = cnt;
    if (n <= k) return puts("0"), 0;

    ll sum = 0, len = 0;
    // for (int i = 1; i <= n; i++) dbg(a[i].first, a[i].second);
    for (int i = n; i >= 1; i--) {
        len += a[i].second;
        suf[i] = len;
        sum += a[i].first * a[i].second;
    }

    for (int i = n; i >= 1; i--) {
        // dbg(i, suf[i]);
        // for (int j = 1; j <= k; j++) {
        //     dbg(j, mx[j], opt[j]);
        // }
        for (int j = k; j >= 1; j--) {
            dp[j][i] = mx[j] + opt[j] * (a[i].first - a[i - 1].first);
            if (mx[j - 1] + suf[i] * (a[i].first - a[i - 1].first) >= dp[j][i]) {
                dp[j][i] = mx[j - 1] + suf[i] * (a[i].first - a[i - 1].first);
                opt[j] = suf[i];
            }
            mx[j] = dp[j][i];
            // dbg(j, dp[j][i], opt[j]);
        }
    }
    // dbg(sum, dp[k][1]);
    cout << sum - dp[k][1];
    return 0;
}