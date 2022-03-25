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
const int maxn = 100000 + 5;

int mu[maxn], vis[maxn], prime[maxn], tot;
void getMu() {
    mu[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!vis[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] < maxn; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

int n, a[maxn], b[maxn];
ll d[maxn], c[maxn];

int main() {
    getMu();
    int T; scanf("%d", &T);
    while (T--) {
        ms(d, 0); ms(c, 0);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= n; i++) scanf("%d", b + i);
        for (int k = 1; k <= n; k++) {
            ll s1 = 0, s2 = 0;
            for (int i = k; i <= n; i += k) s1 += a[i];
            for (int i = k; i <= n; i += k) s2 += b[i];
            d[k] = s1 * s2;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; 1ll * i * j <= n; j++) {
                c[i] += mu[j] * d[i * j];
            }
        }
        for (int i = 1; i <= n; i++) printf("%lld%c", c[i], " \n"[i == n]);
    }
    return 0;
}