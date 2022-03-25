#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int inf = 1 << 30;

int n, q, a[maxn], s[maxn];
// vector<int> v, s, l; 

int dp[maxn][20];
void init(){
    for (int i = 1; i <= n; i++) dp[i][0] = s[i];
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) <= n + 1; i++)
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int rmq(int l, int r){
    int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int main(){
    while (scanf("%d%d", &n, &q) == 2 && n){
        ms(s, 0); a[0] = inf;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            if (a[i] == a[i - 1]) s[i] = s[i - 1] + 1;
            else s[i] = 1;
        }
        init();
        int l, r;
        while (q--){
            scanf("%d%d", &l, &r);
            int t = a[l], ans = 0;
            while (l <= r && a[l] == t) l++, ans++;
            if (l <= r) ans = max(ans, rmq(l, r));
            printf("%d\n", ans);
        }
    }
    return 0;
}