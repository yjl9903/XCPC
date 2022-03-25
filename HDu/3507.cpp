#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, m, q[maxn];
ll a[maxn], dp[maxn];

ll cal(int i) {
    return dp[i] + a[i] * a[i];
}
bool cross(int i, int j, int k) {
    ll y1 = cal(j) - cal(i), x1 = a[j] - a[i];
    ll y2 = cal(k) - cal(j), x2 = a[k] - a[j];
    return x1 * y2 - x2 * y1 <= 0;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++) scanf("%lld", a + i), a[i] += a[i - 1];
        int l = 1, r = 1; q[1] = 0;
        for (int i = 1; i <= n; i++) {
            while (l < r && cal(q[l + 1]) - cal(q[l]) <= 2ll * a[i] * (a[q[l + 1]] - a[q[l]])) l++;
            dp[i] = m + dp[q[l]] + (a[i] - a[q[l]]) * (a[i] - a[q[l]]);
            while (l < r && cross(q[r - 1], q[r], i)) r--;
            q[++r] = i;
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}