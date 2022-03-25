#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define ms(a,b) memset(a,b,sizeof(a))
#define lld I64d
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
#else
  #define dbg(...)
#endif
void err() { std::cout << '\n'; }
template < typename T, typename...Args >
void err(T a, Args...args){ std::cout << a << ' '; err(args...); }
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const ll mod = 998244353;

int n, k;
ll dp[maxn][maxn << 1][2][2] = {0};

int main(){
    scanf("%d%d", &n, &k);
    if (k == 1 || k == 2 * n){puts("2"); return 0;}
    dp[1][1][0][0] = dp[1][1][1][1] = 1;
    dp[1][2][0][1] = dp[1][2][1][0] = 1;
    for (int i = 2; i <= n; i++){
        for (int j = 1; j <= k; j++){
            (dp[i][j][0][0] += dp[i - 1][j][0][0] + dp[i - 1][j - 1][1][1] + dp[i - 1][j][0][1] + dp[i - 1][j][1][0]) %= mod;
            (dp[i][j][1][1] += dp[i - 1][j][1][1] + dp[i - 1][j - 1][0][0] + dp[i - 1][j][0][1] + dp[i - 1][j][1][0]) %= mod;
            (dp[i][j][0][1] += dp[i - 1][j - 1][0][0] + dp[i - 1][j][0][1] + dp[i - 1][j - 1][1][1]) %= mod;
            (dp[i][j][1][0] += dp[i - 1][j - 1][0][0] + dp[i - 1][j][1][0] + dp[i - 1][j - 1][1][1]) %= mod;
            if (j >= 2) (dp[i][j][0][1] += dp[i - 1][j - 2][1][0]) %= mod, (dp[i][j][1][0] += dp[i - 1][j - 2][0][1]) %= mod;
            dbg(i, j);
            dbg(dp[i][j][0][0], dp[i][j][0][1], dp[i][j][1][0], dp[i][j][1][1]);
        }
    }
    ll ans = 0;
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) (ans += dp[n][k][i][j]) %= mod;
    printf("%lld", ans);
    return 0;
}