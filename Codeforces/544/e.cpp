#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 5000 + 5;

int n, nn, k, a[maxn], c[maxn]; 
map<int,int> mp;
int dp[maxn][maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, x; i <= n; i++) scanf("%d", &x), mp[x]++;
    for (auto& x: mp) {
        nn++; a[nn] = x.first; c[nn] = x.second;
    }
    for (int i = 1; i <= nn; i++) {
        int tot = 0;
        for (int l = 0; l <= k; l++) dp[i][l] = dp[i - 1][l];
        for (int j = i; j >= 1 && a[j] >= a[i] - 5; j--) {
            tot += c[j];
            for (int l = 0; l < k; l++) {
                dp[i][l + 1] = max(dp[i][l + 1], dp[j - 1][l] + tot);
            }
        }
    }
    int ans = dp[nn][k];
    for (int i = 1; i <= nn; i++) ans = max(ans, dp[i][k]);
    cout << ans << endl;
    return 0;
}