#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int inf = 1 << 30;

int n, a[maxn], dp[maxn][maxn];

int dfs(int l, int r){
    if (dp[l][r]) return dp[l][r];
    if (r - l <= 1) {
        return dp[l][r] = abs(a[r] - a[l]);
    }
    int ans1 = a[l], ans2 = a[r];
    if (a[l + 1] >= a[r]) ans1 += dfs(l + 2, r) - a[l + 1];
    else ans1 += dfs(l + 1, r - 1) - a[r];
    if (a[l] >= a[r - 1]) ans2 += dfs(l + 1, r - 1) - a[l];
    else ans2 += dfs(l, r - 2) - a[r - 1];
    return dp[l][r] = max(ans1, ans2);
}

int main(){
    int kase = 0;
    while (~scanf("%d", &n), n){
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        ms(dp, 0);
        printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++kase, dfs(1, n));
    }
    return 0;
}