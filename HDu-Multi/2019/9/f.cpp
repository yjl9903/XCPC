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

int n, a[maxn], usd[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int ans = 0, res = inf, mx = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            usd[i] = 0;
            if (a[i] > 400) {
                int s = 0;
                if (a[i] % 400 == 0) s = a[i] - 400;
                else s = a[i] - a[i] % 400;
                ans = max(ans, s / 100);
                usd[i] = s / 100;
                dbg(s);
            }
            if (a[i] % 400 == 0) a[i] = 400;
            else a[i] = a[i] % 400;
            mx = max(mx, a[i]);
        }
        dbg(ans);
        for (int i = 0; i * 10 <= 400; i++) {
            for (int j = 0; j * 20 <= 400; j++) {
                for (int k = 0; k * 50 <= 400; k++) {
                    for (int p = 0; p * 100 <= 400; p++) {
                        int sum = i * 10 + j * 20 + k * 50 + p * 100, cnt = 0;
                        // if (sum < mx) continue;
                        if (i + j + k + p > res) continue;
                        for (int id = 1; id <= n; id++) {
                            int d = a[id];
                            if (d / 100 <= p + ans - usd[id]) d -= d / 100 * 100;
                            if (d / 50 <= k) d -= d / 50 * 50;
                            if (d / 20 <= j) d -= d / 20 * 20;
                            if (d / 10 <= i) d -= d / 10 * 10;
                            if (d == 0) cnt++;
                        }
                        if (cnt == n) res = min(res, i + j + k + p);
                    }
                }
            }
        }
        if (res == inf) puts("-1");
        else printf("%d\n", ans + res);
    }
    return 0;
}