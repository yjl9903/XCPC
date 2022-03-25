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
const ll inf = 1e9 + 7;
const int maxn = 200 + 5;
const int maxm = 10000 + 5;

int m, n, k, xx[maxn];
vector<PII> task[maxn];
ll cost[maxn], dp[maxn][maxm];
int val[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &m, &n, &k);
        for (int i = 1, tp; i <= n; i++) {
            scanf("%d", &tp);
            if (tp == 0) {
                scanf("%d", val + i);
                cost[i] = inf;
            } else {
                scanf("%lld%d", cost + i, val + i);
            }
        }
        for (int i = 1, y; i <= k; i++) {
            scanf("%d%d", xx + i, &y); task[i].clear();
            while (y--) {
                int u, v; scanf("%d%d", &u, &v);
                task[i].push_back({u, v});
            }
        }
        while (true) {
            bool flag = 1;
            for (int i = 1; i <= k; i++) {
                ll sum = 0;
                for (auto& x: task[i]) sum += cost[x.first] * x.second;
                if (cost[xx[i]] > sum) {
                    flag = 0; cost[xx[i]] = sum;
                }
            }
            if (flag) break;
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= cost[i]) dp[i][j] = max(dp[i][j], dp[i][j - cost[i]] + val[i]);
            }
        }
        printf("Case #%d: %lld\n", ++kase, dp[n][m]);
    }
    return 0;
}