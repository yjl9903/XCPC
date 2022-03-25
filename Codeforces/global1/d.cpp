#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 1000000 + 5;

int n, m, cnt[maxn], dp[maxn][3][3];

// dp[i][3][3], 

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0, x; i < n; i++) scanf("%d", &x), cnt[x]++;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) for (int h = 0; h < 3; h++) {
            if (cnt[i] < j + k + h) break;
            dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][h] + (cnt[i] - j - k - h) / 3 + j);
        }
    }
    cout << dp[m][0][0] << endl;
    return 0;
}