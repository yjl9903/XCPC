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

int n, m, g[20][20], ones[1 << 15];
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
        for (int i = 0; i < n; i++) {
            int c = ones[s];
            if ((s & (1 << i)) && dp[s][i] != -1) {
                for (int j = 0; j < n; j++) {
                    if (i != j && (s & (1 << j)) == 0 && g[i][j]) {
                        // dbg(1);
                        dp[s | (1 << j)][j] = max(dp[s | (1 << j)][j], dp[s][i] + 1ll * g[i][j] * c * (n - c));
                        dp[s | (1 << j)][i] = max(dp[s | (1 << j)][i], dp[s][i] + 1ll * g[i][j] * (n - 1));
                    }
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