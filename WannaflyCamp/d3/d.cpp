#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, m, g[20][20], ones[1 << 15], tmp0[30], tmp1[30];
ll dp[1 << 15][20];

int main(){
    for (int i = 1; i < (1 << 15); i++) {
        int cnt = 0, x = i;
        while (x) {
            if (x & 1) cnt++;
            x >>= 1;
        }
        ones[i] = cnt;
    }
    ms(dp, -1);
    scanf("%d%d", &n, &m);
    while (m--) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g[u][v] = g[v][u] = w;
    }
    int ss = 1 << n;
    for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
    for (int s = 1; s < ss; s++) {
        for (int s0 = s; s0; s0 = (s0 - 1) & s) {
            int s1 = s ^ s0;
            int l0 = 0, l1 = 0;
            for (int i = 0; i < n; i++) if (s0 & (1 << i)) tmp0[l0++] = i;
            for (int i = 0; i < n; i++) if (s1 & (1 << i)) tmp1[l1++] = i;
            // for (int i = 0; i < n; i++) {
            for (int k0 = 0; k0 < l0; k0++) {
                int i = tmp0[k0];
                if ((s0 & (1 << i)) == 0 || dp[s0][i] == -1) continue;
                // for (int j = 0; j < n; j++) {
                for (int k1 = 0; k1 < l1; k1++) {
                    int j = tmp1[k1];
                    if ((s1 & (1 << j)) == 0 || g[i][j] == 0 || dp[s1][j] == -1) continue;
                    // ll tot = dp[s0][i] + dp[s1][j] + 1ll * g[i][j] * max();
                    dp[s][i] = max(dp[s][i], dp[s0][i] + dp[s1][j] + 1ll * g[i][j] * ones[s1] * (n - ones[s1]));
                    dp[s][j] = max(dp[s][j], dp[s0][i] + dp[s1][j] + 1ll * g[i][j] * ones[s0] * (n - ones[s0]));
                }
            }
        }
    }
    // for (int i = 1; i < ss; i++) {
    //     dbg(i, dp[i][0], dp[i][1], dp[i][2], dp[i][3], dp[i][4]);
    // }
    ll ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, dp[ss - 1][i]);
    cout << ans;
    return 0;
}