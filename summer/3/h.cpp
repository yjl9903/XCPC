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
const int maxn = 1 << 10;

int n, m, dp[20][maxn + 10];
vector<int> c[20], d[20], sta[20];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            int k, x; scanf("%d", &k); c[i].clear();
            while (k--) {
                scanf("%d", &x); c[i].push_back(x);
            }
        }
        for (int i = 0; i < m; i++) {
            int k, x; scanf("%d", &k); d[i].clear();
            while (k--) {
                scanf("%d", &x); d[i].push_back(x);
            }
        }
        int ss = 1 << m;
        for (int i = 0; i < n; i++) {
            sta[i].clear();
            for (int s = 0; s < ss; s++) {
                vector<int> cnt(101, 0);
                for (int j = 0; j < m; j++) if (s & (1 << j)) {
                    for (int& x: d[j]) cnt[x]++;
                }
                int f = 1;
                for (int x: c[i]) if (!cnt[x]) {
                    f = 0; break;
                }
                if (f) sta[i].push_back(s);
            }
        }
        ms(dp, 0); int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < ss; j++) {
                for (int& s: sta[i]) if ((j | s) == j) {
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j ^ s] + 1);
                }
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                ans = max(dp[i + 1][j], ans);
            }
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}