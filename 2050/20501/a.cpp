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
const int maxn = 300000 + 5;

int n, m, y, a[maxn], b[maxn];
double dp[maxn][2];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &y);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= m; i++) scanf("%d", b + i);
        for (int i = 0; i < maxn; i++) dp[i][0] = dp[i][1] = 0;
        dp[0][0] = 1;
        for (int i = 0; i < maxn; i++) {
            for (int j = 1; j <= n; j++) {
                if (i + a[j] > maxn) continue;
                // dp[i + a[i]] += (1 - dp[i]) * 1.0 / double(n + m);
                dp[i + a[j]][1] += dp[i][0] * 1.0 / double(n + m);
            }
            for (int j = 1; j <= m; j++) {
                if (i + b[j] > maxn) continue;
                dp[i + b[j]][0] += dp[i][0] * 1.0 / double(n + m);
            }
        }
        double e = 0;
        for (int i = 1; i < maxn; i++) e += i * dp[i][1];
        // cout << e << endl;
        if (e <= y) puts("Go");
        else puts("Wait");
    }
    return 0;
}