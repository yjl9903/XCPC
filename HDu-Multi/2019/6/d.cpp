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
typedef pair<ll,ll> PLL;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

PLL add(PLL a, PLL b) {
    PLL ans;
    ll t = a.first * b.second + a.second * b.first;
    ll d = a.second * b.second;
    ll g = __gcd(t, d);
    ans.first = t / g;
    ans.second = d / g;
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        PLL x = { 0, 1 };
        for (int i = 1, a, b; i <= n; i++) {
            scanf("%d%d", &a, &b);
            x = add(x, { 1ll * a * b, a + b });
            printf("%lld/%lld\n", x.first, x.second);
        }
    }
    return 0;
}