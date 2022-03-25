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
const int maxn = 2100 + 5;

int n, f[maxn], dp[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int ans = 0;
        for (int i = 1; i < n; i++) {
            scanf("%d", f + i);
            if (i > 1) f[i] -= f[1];
        }
        ans = n * f[1];
        for (int i = 1; i <= n - 2; i++) f[i] = f[i + 1], dp[i] = f[i];
        for (int i = 1; i <= n - 2; i++) {
            for (int j = i; j <= n - 2; j++) {
                dp[j] = max(dp[j], dp[j - i] + f[i]);
            }
        }
        printf("%d\n", ans + dp[n - 2]);
    }
    return 0;
}