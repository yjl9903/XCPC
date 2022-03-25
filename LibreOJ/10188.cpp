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
const int maxn = 50000 + 5;

int n, L, c[maxn], q[maxn];
ll pre[maxn], dp[maxn];

ll gu(int i, int j) {
    return dp[i] + pre[i] * pre[i] - dp[j] - pre[j] * pre[j];
}
ll gd(int i, int j) {
    return pre[i] - pre[j];
}

int main() {
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i); pre[i] = pre[i - 1] + c[i];
    }
    for (int i = 1; i <= n; i++) pre[i] += i;
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        while (l < r && gu(q[l + 1], q[l]) < 2 * gd(q[l + 1], q[l]) * (pre[i] - 1 - L)) l++;
        int j = q[l];
        dp[i] = dp[j] + (pre[i] - pre[j] - 1 - L) * (pre[i] - pre[j] - 1 - L);
        dbg(i, dp[i], l, r);
        while (l < r && gu(q[r], q[r - 1]) * gd(i, q[r]) >= gu(i, q[r]) * gd(q[r], q[r - 1])) r--;
        q[++r] = i;
    }
    cout << dp[n];
    return 0;
}