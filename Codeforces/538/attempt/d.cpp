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

int f[maxn][maxn];
int dp(int l, int r) {
    if (f[l][r] != -1) return f[l][r];
    if (l == r) return 0;
    if (l > r) return 1;
    int ans = mod;
    if (a[l] == a[r]) ans = dp(l + 1, r - 1) + 1;
    ans = min(ans, dp(l + 1, r) + 1);
    ans = min(ans, dp(l, r - 1) + 1);
    return f[l][r] = ans;
}

int main() {
    ms(f, -1);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i);
        a[i] = c[i];
        if (c[i] != c[i - 1]) a[++len] = c[i];
    }
    cout << dp(1, len) << endl;
    return 0;
}