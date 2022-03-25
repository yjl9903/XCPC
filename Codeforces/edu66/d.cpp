#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, a[maxn], k;
ll suf[maxn];

int dp[maxn][20];
void init() {
    for (int i = 1; i <= n; i++) dp[i][0] = i;
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) <= n + 1; i++) {
            if (suf[dp[i][j - 1]] < suf[dp[i + (1 << (j - 1))][j - 1]])
                dp[i][j] = dp[i + (1 << (j - 1))][j - 1];
            else 
                dp[i][j] = dp[i][j - 1];
        }
}
int rmq(int l, int r) {
    int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int main() {
    scanf("%d%d", &n, &k);
    ll ans = 0;
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = n; i >= 1; i--) suf[i] = a[i] + suf[i + 1];
    ans = suf[1];
    vector<ll> v;
    for (int i = 2; i <= n; i++) v.push_back(suf[i]);
    sort(v.begin(), v.end(), [](ll a, ll b) { return a > b; });
    for (int i = 0; i < k - 1; i++) ans += v[i];

    // init();
    // int st = 2;
    // ans = suf[1];
    // for (int i = 2; i <= k; i++) {
    //     int p = rmq(st, n - k + i);
    //     // cout << ans << ' ' << p << endl;
    //     ans += suf[p];
    //     st = p + 1;
    // }
    cout << ans;
    return 0;
}