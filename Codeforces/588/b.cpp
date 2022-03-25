#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace {
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
}

vector<int> edge[maxn];
int n, ans; ll a[maxn];

void dfs(int u, int ff, map<ll,int> fmp) {
    map<ll,int> mp; mp[a[u]] = 1;
    for (auto& x: fmp) {
        mp[__gcd(x.first, a[u])] += x.second;
    }
    for (auto& x: mp) {
        ans = add(ans, mul(x.first % mod, x.second));
    }
    for (int v: edge[u]) {
        if (v == ff) continue;
        dfs(v, u, mp);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld\n", a + i);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0, map<ll,int>());
    cout << ans;
    return 0;
}