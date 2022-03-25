#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, d;
ll dp[100] = {0, 1};

ll dfs(int x){
    if (x < 1) return 0;
    // if (x == 1) return 1;
    if (dp[x]) return dp[x];
    ll k = 1;
    k += dfs(x - 1);
    k += dfs(x - d - 1);
    // cout << x << ' ' << k << endl;
    return dp[x] = k;
}

int main(){
    scanf("%d%d", &n, &d);
    if (n <= 1){
        puts("0"); return 0;
    }
    ll ans = 1ll << (n - 1);
    if (d == n) printf("%lld\n", ans - 1);
    else{
        ll ans2 = dfs(n - d - 1);
        // cout << ans2 << endl;
        printf("%lld\n", ans - 1 - ans2);
    }
    return 0;
}