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
const int maxn = 600000 + 5;

int n, a[maxn];
ll pre[maxn], suf[maxn];

int dp[20][maxn];
void init() {
    for (int i = 1; i <= n; i++) dp[0][i] = i;
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) <= n + 1; i++) {
            int l = dp[j - 1][i];
            int r = dp[j - 1][i + (1 << (j - 1))];
            if (a[l] > a[r]) dp[j][i] = l;
            else dp[j][i] = r;
        }
}
int qmax(int l, int r) {
    int k = __lg(r - l + 1);
    int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
    if (a[x] > a[y]) return x;
    else return y;
}

ll ans;
ll solve(int l, int r) {
    if (l >= r) return 0;
    int m = qmax(l, r);
    dbg(l, r, m);
    ll ans = 0;
    if (m - l < r - m) {
        for (int i = l; i <= m; i++) {
            int pos = lower_bound(pre + m, pre + r + 1, 2ll * a[m] + pre[i - 1]) - pre;
            dbg(1, i, pos);
            ans += r - pos + 1;
        }
    } else {
        for (int i = m; i <= r; i++) {
            int pos = upper_bound(pre + l - 1, pre + m, pre[i] - 2ll * a[m]) - pre;
            dbg(2, i, pos);
            ans += pos - l + 1;
        }
    }
    return ans + solve(l, m - 1) + solve(m + 1, r);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        pre[0] = suf[n + 1] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            pre[i] = pre[i - 1] + a[i];
        }
        for (int i = n; i >= 1; i--) suf[i] = suf[i + 1] + a[i];
        init();
        printf("%lld\n", solve(1, n));
    }
    return 0;
}