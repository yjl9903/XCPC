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
const int maxn = 100 + 5;

int n, a[maxn];
PII b[maxn];

int dp[maxn][maxn];
int dfs(int l, int r) {
    if (dp[l][r]) return dp[l][r];
    if (l + 1 == r) return b[l].first * b[l].second * b[r].second;
    if (l >= r) return 0;
    int mn = 2e9;
    for (int k = l; k < r; k++) {
        mn = min(mn, dfs(l, k) + dfs(k + 1, r) + b[l].first * b[k].second * b[r].second);
    }
    return dp[l][r] = mn;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i < n; i++) b[i].first = a[i], b[i].second = a[i + 1];
    cout << dfs(1, n - 1) << endl;
    return 0;
}