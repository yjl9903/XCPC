#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 10007;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

int n, k, S[505][505];
vector<int> edge[maxn];

int dp[maxn][505], dp2[maxn][505];
void dfs1(int u, int f) {
    dp[u][0] = 1;
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs1(v, u);
        for (int i = 1; i <= k; i++) {
            dp[u][i] = add(dp[u][i], (dp[v][i] + i * dp[v][i - 1]) % mod);
        }
        dp[u][0] = add(dp[u][0], dp[v][0]);
    }
}
void dfs2(int u, int f) {
    for (int v: edge[u]) {
        if (v == f) continue;
        vector<int> tmp(k + 1, 0);
        tmp[0] = sub(dp2[u][0], dp[v][0]);
        for (int i = 1; i <= k; i++) 
            tmp[i] = sub(dp2[u][i], (dp[v][i] + i * dp[v][i - 1]) % mod);
        for (int i = 1; i <= k; i++) 
            dp2[v][i] = add(dp[v][i], (tmp[i] + i * tmp[i - 1]) % mod);
        dp2[v][0] = add(dp[v][0], tmp[0]);
        dfs2(v, u);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    S[1][1] = 1;
    for (int i = 2; i <= k; i++) {
        for (int j = 1; j <= i; j++) {
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % mod;
        }
    }
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs1(1, 0); 
    for (int i = 0; i <= k; i++) dp2[1][i] = dp[1][i];
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int j = 1; j <= k; j++) {
            ans = add(ans, mul(S[k][j], dp2[i][j]));
        }
        printf("%d\n", ans);
    }
    return 0;
}