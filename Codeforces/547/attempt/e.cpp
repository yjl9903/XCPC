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
const int maxn = 200000 + 5;

ll h, d[maxn], mn = 1e18; int n;

bool check(ll x) {
    ll sum = x * d[n] + mn;
    return sum + h <= 0;
}

int main() {
    scanf("%I64d%d", &h, &n);
    for (int i = 1; i <= n; i++) scanf("%I64d", d + i), d[i] += d[i - 1], mn = min(mn, d[i]);

    for (int i = 0; i <= n; i++) if (h + d[i] <= 0) {
        printf("%d", i); return 0;
    }
    if (d[n] >= 0) return puts("-1"), 0;
    
    ll l = 0, r = 1e15, t = 1;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (check(m)) t = m, r = m - 1;
        else l = m + 1;
    }
    t--;
    h += t * d[n];
    for (int i = 0; i <= n; i++) if (h + d[i] <= 0) {
        printf("%I64d", t * n + i); return 0;
    }
    h += d[n]; t++;
    for (int i = 0; i <= n; i++) if (h + d[i] <= 0) {
        printf("%I64d", t * n + i); return 0;
    }
    h += d[n]; t++;
    for (int i = 0; i <= n; i++) if (h + d[i] <= 0) {
        printf("%I64d", t * n + i); return 0;
    }
    puts("-1");
    return 0;
}