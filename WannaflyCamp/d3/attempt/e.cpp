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
const int mod = 998244353;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, m, k[maxn];

int dp[maxn][2];
void dfs(int u, int f) {
    int s1 = 0, s2 = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        s1 += max(dp[v][0], dp[v][1]);
        s2 += dp[v][0];
    }
    dp[u][0] = s1; dp[u][1] = s2;
}
int dp2[maxn][2], ff[maxn], g[maxn]; // greedy, rebuild greedy
int dfs2(int u, int f) {
    if ((int)edge[u].size() <= 1) {
        dp2[u][1] = 1; g[u] = 1; return 1;
    }
    int s1 = 0, s2 = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs2(v, u);
        s1 += max(dp[v][0], dp[v][1]);
        s2 += dp[v][0];
    }
    dp2[u][0] = s1; dp2[u][1] = s2;
    return 0;
}
void dfs3(int u, int f, int k1, int k2) {
    if ((int)edge[u].size() <= 1) {
        ff[u] = k2; g[u] = 1; return;
    }
    int s1 = max(k1, k2), s2 = k1 + 1; 
    // s1: not choose u; s2: choose u
    for (int& v: edge[u]) {
        if (v == f) continue;
        s1 += max(dp[v][0], dp[v][1]);
        s2 += dp[v][0];
    }
    ff[u] = max(s1, s2);
    int flag = 0;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs3(v, u, s1 - max(dp[v][0], dp[v][1]), s2 - dp[v][0]);
        flag = g[v];
    }
    if (flag) {
        g[u] = 0; 
        if (s2 > s1) dbg("?", s1, s2, u);
    } else {
        if (s2 >= s1) g[u] = 1;
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1; i <= m; i++) scanf("%d", k + i);
    dfs(1, 0); dfs2(1, 0); dfs3(1, 0, 0, 0);
    for (int i = 1; i <= n; i++) {
        dbg(i, ff[i], g[i]);
    }
    int ans = max(dp[1][0], dp[1][1]), last = 0; // 0: not choose
    if (dp[1][1] > dp[1][0]) last = 1;
    printf("%d\n", ans);
    for (int i = 1; i <= m; i++) {
        dbg(last);
        ans = 1ll * ans * n % mod;
        if (last == 0) {
            ans = (ans + ff[k[i]]) % mod;
            last = g[k[i]];
        } else last = 0;
        printf("%d\n", ans);
    }
    return 0;
}