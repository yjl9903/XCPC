#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200 + 5;

int n, a[maxn];
char s[maxn];

ll f[maxn][maxn][maxn];
ll dp(int l, int r, int pre) {
    if (l > r) return 0;
    if (l == r) return a[pre];
    if (f[l][r][pre]) return f[l][r][pre];
    ll ans = a[pre] + dp(l + 1, r, 1);
    for (int i = l + 1; i <= r; i++) {
        if (s[i] == s[l]) {
            ans = max(ans, dp(l + 1, i - 1, 1) + dp(i, r, pre + 1));
        }
    }
    return f[l][r][pre] = ans;
}

int main(){
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    cout << dp(1, n, 1) << endl;
    return 0;
}