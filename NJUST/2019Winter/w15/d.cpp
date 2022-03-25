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
const int maxn = 500 + 5;
int mod;

int n, m, cnt[maxn];
char s[maxn];
ll dp[2][maxn][maxn];

void add(ll &x, ll k) {
    x += k; if (x >= mod) x -= mod;
}

int main() {
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 1; i <= m; i++) {
        scanf("%s", s);
        for (int i = 0; i < n; i++) if (s[i] == '1') cnt[i + 1]++;
    }
    int f = 0, c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++) if (cnt[i] == 1) c1++; else if (cnt[i] == 0) c2++;
    // cout << c1 << ' ' << c2 << endl;
    dp[0][c1][c2] = 1;
    for (int t = m + 1; t <= n; t++, f ^= 1) {
        ms(dp[f ^ 1], 0);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; i + j <= n; j++) {
                if (dp[f][i][j] == 0) continue;
                if (i >= 2)
                    add(dp[f ^ 1][i - 2][j], dp[f][i][j] * (i * (i - 1) / 2) % mod);
                if (j >= 2)
                    add(dp[f ^ 1][i + 2][j - 2], dp[f][i][j] * (j * (j - 1) / 2) % mod);
                if (i >= 1 && j >= 1)
                    add(dp[f ^ 1][i][j - 1], dp[f][i][j] * i * j % mod);
            }
        }
    } 
    cout << dp[f][0][0] << endl;
    return 0;
}