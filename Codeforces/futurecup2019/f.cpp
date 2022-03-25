#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv(ll x) {
    return qpow(x, mod - 2);
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}
void sub(ll& x, ll y) {
    x -= y; if (x < 0) x += mod;
}
void mul(ll& x, ll y) {
    x = x * y % mod;
}

vector<int> edge[maxn];
int n;

ll dp[maxn][3];
// dp[leaf][2] = 1, otherwise dp[u][2] = 0
void dfs(int u) {
    if (edge[u].empty()) {
        dp[u][2] = 1; return ;
    }
    dp[u][0] = 1;
    int cnt = 0;
    for (int& v: edge[u]) {
        dfs(v);
        dp[u][2] = ((dp[u][1] + dp[u][2]) * (dp[v][2] + dp[v][1]) + dp[u][2] * (dp[v][0] + dp[v][2])) % mod;
        // root's half subgraph and subgraph connect to child's subgraph or child's subgrah
        // root's subgraph dont connect to child's subgraph and no graph
        dp[u][1] = (dp[u][0] * (dp[v][2] + dp[v][1]) + dp[u][1] * (dp[v][0] + dp[v][2])) % mod;
        // root's no graph connect to child's subgraph and half subgraph
        // root's half subgraph dont connect to child's ...
        mul(dp[u][0], dp[v][0] + dp[v][2]);
        // root dont connect to child's ...
    }
    // dbg(u, dp[u][0], dp[u][1], dp[u][2]);
}

int main() {
    scanf("%d", &n);
    for (int i = 2, p; i <= n; i++) {
        scanf("%d", &p); edge[p].push_back(i);
    }
    dfs(1);
    cout << (dp[1][0] + dp[1][2]) % mod;
    return 0;
}