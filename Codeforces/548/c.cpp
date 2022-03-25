#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
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

vector<PII> edge[maxn];
int n, k, siz[maxn];
ll ans = 0;

void dfs(int u, int f, int k) {
    siz[u] = 1;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        if (x.second) {
            dfs(v, u, 1);
        } else {
            dfs(v, u, 0);
            siz[u] += siz[v];
        }
    }
    if (k) {
        ans += qpow(siz[u], ::k);
        if (ans >= mod) ans -= mod;
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, u, v, x; i < n; i++) {
        scanf("%d%d%d", &u, &v, &x);
        edge[u].push_back({v, x});
        edge[v].push_back({u, x});
    }
    dfs(1, 0, 1);
    cout << (qpow(n, k) - ans + mod) % mod << endl;
    return 0;
}