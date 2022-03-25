#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], pos[maxn];

int dp[maxn][20];
void init() {
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) <= n + 1; i++)
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int qmax(int l, int r) {
    int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
}

ll solve(int l, int r) {
    if (r - l <= 1) return 0;
    int mx = qmax(l, r), mid = pos[mx];
    ll ans = 0;
    if (mid - l < r - mid) {
        for (int i = l; i < mid; i++) if (pos[mx - a[i]] > mid && pos[mx - a[i]] <= r) ans++;
    } else {
        for (int i = mid + 1; i <= r; i++) if (pos[mx - a[i]] < mid && pos[mx - a[i]] >= l) ans++;
    }
    return ans + solve(l, mid - 1) + solve(mid + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), dp[i][0] = a[i], pos[a[i]] = i;
    init();
    cout << solve(1, n) << endl;
    return 0;
}