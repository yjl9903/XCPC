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

int qpow(int x, int n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
int inv(int x) {
    return qpow(x, mod - 2);
}
int inv2 = qpow(2, mod - 2);
int add(int x, int y) {
    x += y; if (x >= mod) x -= mod;
    return x;
}
int sub(int x, int y) {
    x -= y; if (x < 0) x += mod;
    return x;
}

int n, a[maxn], b[maxn], c[maxn];

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= n; i++) b[i] = inv(a[i]), c[i] = 1ll * a[i] * a[i] % mod;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                b[i] = 1ll * b[i] * inv(sub(c[j], c[i])) % mod;
                b[j] = 1ll * b[j] * inv(sub(c[i], c[j])) % mod;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) ans = add(ans, b[i]);
        printf("%d\n", 1ll * ans * inv2 % mod);
    }
    return 0;
}