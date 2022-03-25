#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, dp[20];
int a[20], c;

ll dfs(int p, int lim){
    if (p == -1) return 1;
    if (!lim && dp[p] != -1) return dp[p];
    int end = lim ? a[p] : 9;
    ll ans = 0;
    for (int i = 0; i <= end && i <= (p == 0 ? 2 : 3); i++){
        ans += dfs(p - 1, lim && i == end);
    }
    if (!lim) dp[p] = ans;
    return ans;
}

int main(){
    while (~scanf("%lld",&n)){
        ll x = n - 1; c = 0;
        while (x){
            a[c++] = x % 10;
            x /= 10;
        }
        ms(dp, -1); ll ans = dfs(c - 1, 1);
        printf("%lld\n", ans);
    }
    return 0;
}