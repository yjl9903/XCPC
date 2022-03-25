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
const int maxn = 2000 + 5;

int n, m, k, dp[maxn][maxn];
PII a[maxn], b[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &a[i].first, &a[i].second);
        }
        sort(a + 1, a + 1 + m, [](PII a, PII b) {
            if (a.first == b.first) return a.second > b.second;
            return a.first < b.first;
        });
        int pos = 0, len = 0;
        for (int i = 0; i < n; i++) {
            while (pos < m && a[pos + 1].first == i + 1) {
                pos++;
                len = max(len, a[pos].second - a[pos].first + 1);
            }
            for (int j = 0; j <= k; j++) {
                dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
                dp[i + len][j + 1] = max(dp[i + len][j + 1], dp[i][j] + len);
            }
            if (len) len--;
        }
        printf("Case #%d: %d\n", ++kase, dp[n][k]);
        ms(dp, 0);
    }
    return 0;
}