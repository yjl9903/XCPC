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
const int maxn = 4000001 + 5;

ll phi[maxn], ans[maxn];
void init(int n) {
    for (int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        if (!phi[i])
        for (int j = i; j <= n; j += i) {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    for (int i = 2; i <= n; i++) phi[i] += phi[i - 1];
}

int main() {
    init(maxn - 1);
    int n;
    while (scanf("%d", &n) == 1 && n) {
        ll ans = 0;
        for (ll d = 1; d <= n; d++) ans += 1ll * d * phi[n / d] - d;
        printf("%lld\n", ans);
    }
    return 0;
}