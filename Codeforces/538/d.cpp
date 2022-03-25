#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 5000 + 5;

int n, c[maxn], a[maxn], len;

int f[maxn][maxn][2];
int dp(int l, int r, int t) {
    if (f[l][r][t] != -1) return f[l][r][t];
    if (l == r) return 0;
    int ans = 0;
    if (t == 0) {
        ans = dp(l + 1, r, 0) + (int)(a[l] != a[l + 1]);
        ans = min(dp(l + 1, r, 1) + (int)(a[l] != a[r]), ans);
        ans = min(dp(l, r - 1, 0) + 2 * (int)(a[r - 1] != a[r]), ans);
    } else {
        ans = dp(l + 1, r, 1) + 2 * (int)(a[l] != a[l + 1]);
        ans = min(dp(l, r - 1, 1) + (int)(a[r - 1] != a[r]), ans);
        ans = min(dp(l, r - 1, 0) + (int)(a[l] != a[r]), ans);
    }
    return f[l][r][t] = ans;
}

int main() {
    ms(f, -1);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i);
        a[i] = c[i];
        // if (c[i] != c[i - 1]) a[++len] = c[i];
    }
    len = n;
    cout << min(dp(1, len, 0), dp(1, len, 1)) << endl;
    return 0;
}