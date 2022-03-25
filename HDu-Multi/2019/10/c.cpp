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

int n;
double a[maxn], pre[maxn], suf[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        double mx = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lf", a + i);
            mx = max(mx, a[i]);
        }
        // if (mx >= 0.5) printf("%.8lf\n", mx);
        // else {
            double ans = 0, pd = 1.0;
            sort(a + 1, a + 1 + n);
            reverse(a + 1, a + 1 + n);
            for (int i = 1; i <= n; i++) {
                double tot = ans * (1 - a[i]) + a[i] * pd;
                if (tot < ans) break;
                dbg(i, ans);
                ans = tot;
                pd *= (1 - a[i]);
            }
            // pre[0] = 1.0; suf[n + 1] = 1.0;
            // for (int i = 1; i <= n; i++) {
            //     pre[i] = pre[i - 1] * (1.0 - a[i]);
            // }
            // for (int i = n; i >= 1; i--) {
            //     suf[i] = suf[i + 1] * (1.0 - a[i]);
            // }
            // for (int i = 1; i <= n; i++) {
            //     ans += a[i] * pre[i - 1] * suf[i + 1];
            // }
            printf("%.8lf\n", ans);
        // }
    }
    return 0;
}