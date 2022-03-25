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

int n, f[maxn], siz[maxn];
vector<int> edge[maxn];

int dfs(int u, int ff) {
    siz[u] = 1;
    int r = 1;
    for (int& v: edge[u]) {
        if (v == ff) continue;
        r = 1ll * r * dfs(v, u) % mod;
        // if (siz[v] > 1) r = 2ll * r % mod;
        r = 1ll * r * (int)(edge[v].size()) % mod;
        siz[u] += siz[v];
    }
    dbg(edge[u].size());
    int sz = (int)edge[u].size(); if (u != 1) sz--;
    return 1ll * r * f[sz] % mod;
}

int main() {
    f[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = 1ll * i * f[i - 1] % mod;
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int ans = dfs(1, 0);
    cout << 1ll * n * ans % mod;
    return 0;
}