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
const int maxn = 100 + 5;

int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

int n, m, G[maxn][maxn];

int check(int i, int j, int k, int x) {
    return G[i][j] == x && G[i][k] == x && G[k][j] == x;
}
int check(int i, int j, int k, int p, int x) {
    return check(i, j, k, x) || check(i, j, p, x) || check(i, k, p, x) || check(j, k, p, x);
}
int check(int i, int j, int k, int p, int q, int x) {
    return check(i, j, k, x) || check(i, j, p, x) || check(i, j, q, x)
        || check(i, k, p, x) || check(i, k, q, x) || check(i, p, q, x)
        || check(j, k, p, x) || check(j, k, q, x) || check(j, p, q, x)
        || check(k, p, q, x); 
}

int main() {
    init();
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) G[i][j] = 0;
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v); G[u][v] = G[v][u] = 1;
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                for (int k = j + 1; k <= n; k++) {
                    if (check(i, j, k, 1) || check(i, j, k, 0)) ans++;
                    for (int p = k + 1; p <= n; p++) {
                        if (check(i, j, k, p, 1) || check(i, j, k, p, 0)) ans++;
                        for (int q = p + 1; q <= n; q++) {
                            if (check(i, j, k, p, q, 1) || check(i, j, k, p, q, 0)) ans++;
                        }
                    }
                }
                ans %= mod;
            }
        }
        for (int i = 6; i <= n; i++) ans = (ans + C(n, i)) % mod;
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}