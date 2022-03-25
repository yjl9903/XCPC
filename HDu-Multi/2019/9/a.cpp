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

int g[maxn];
int cal(int n, int m) {
    if (n <= m) return 0;
    if (n == m + 1) return m;
    g[m + 1] = m;
    for (int i = m + 2; i <= n; i++) {
        int ans = 0;
        for (int j = m + 1; j < i; j++) ans = add(ans, g[j]);
        g[i] = i - 1;
        g[i] = add(g[i], mul(ans, mul(2, inv(i))));
    }
    return g[n];
}

int main() {
    int n, m; cin >> n >> m;
    cout << cal(n, m);
    return 0;
}