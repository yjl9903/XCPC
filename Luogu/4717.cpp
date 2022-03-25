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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1 << 18;

int n, a[maxn], b[maxn], c[maxn], d[maxn], e[maxn], f[maxn];

void fwtOR(int a[], int n, int op = 1) {
    for (int d = 1; d < n; d <<= 1)
        for (int i = 0, t = d << 1; i < n; i += t)
            for (int j = 0; j < d; j++) {
                if (op == 1)
                    a[i + j + d] = (a[i + j + d] + a[i + j]) % mod;
                else
                    a[i + j + d] = (a[i + j + d] + mod - a[i + j]) % mod;
            }
}
void fwtAND(int a[], int n, int op = 1) {
    for (int d = 1; d < n; d <<= 1)
        for (int i = 0, t = d << 1; i < n; i += t)
            for (int j = 0; j < d; j++) {
                if (op == 1)
                    a[i + j] = (a[i + j] + a[i + j + d]) % mod;
                else
                    a[i + j] = (a[i + j] + mod - a[i + j + d]) % mod;
            }
}
void fwtXOR(int a[], int n, int op = 1) {
    for (int d = 1; d < n; d <<= 1)
        for (int i = 0, t = d << 1; i < n; i += t)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) % mod;
                a[i + j + d] = (x + mod - y) % mod;
                if (op != 1) {
                    // inv2 = 499122177
                    a[i + j] = 1ll * a[i + j] * 499122177 % mod;
                    a[i + j + d] = 1ll * a[i + j + d] * 499122177 % mod;
                }
            }
}

int main() {
    scanf("%d", &n);
    int m = 1 << n;
    for (int i = 0; i < m; i++) scanf("%d", a + i), c[i] = a[i], e[i] = a[i];
    for (int i = 0; i < m; i++) scanf("%d", b + i), d[i] = b[i], f[i] = b[i];
    fwtOR(a, 1 << n); fwtOR(b, 1 << n);
    for (int i = 0; i < m; i++) a[i] = 1ll * a[i] * b[i] % mod;
    fwtOR(a, 1 << n, -1);
    for (int i = 0; i < m; i++) printf("%d%c", a[i], " \n"[i == m - 1]);
    fwtAND(c, 1 << n); fwtAND(d, 1 << n);
    for (int i = 0; i < m; i++) c[i] = 1ll * c[i] * d[i] % mod;
    fwtAND(c, 1 << n, -1);
    for (int i = 0; i < m; i++) printf("%d%c", c[i], " \n"[i == m - 1]);
    fwtXOR(e, 1 << n); fwtXOR(f, 1 << n);
    for (int i = 0; i < m; i++) e[i] = 1ll * e[i] * f[i] % mod;
    fwtXOR(e, 1 << n, -1);
    for (int i = 0; i < m; i++) printf("%d%c", e[i], " \n"[i == m - 1]);
    return 0;
}