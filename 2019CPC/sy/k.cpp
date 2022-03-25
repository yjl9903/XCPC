#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
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

int k, a[maxn];
ll n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%lld", &k, &n);
        for (int i = 1; i <= 2 * k; i++) {
            scanf("%d", a + i);
            if (i > k) {
                assert(a[i] == a[k + 1]);
            }
        }
        int ans = 0;
        if (n <= k) {
            for (int i = 1; i <= n; i++) ans = add(ans, a[i]);
        } else {
            for (int i = 1; i <= k; i++) ans = add(ans, a[i]);
            ans = add(ans, mul(a[k + 1], (n - k) % mod));
        }
        printf("%d\n", ans);
    }
    return 0;
}