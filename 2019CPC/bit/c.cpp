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
const int maxn = 100000 + 5;

ll ceil(ll a, ll b) {
    return a / b + (bool)(a % b);
}

int n, k, c;
PII a[maxn];

int main() {
    scanf("%d%d%d", &n, &k, &c);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        ll t = ceil(a[i].first, k) - 1;
        ans += t * a[i].second;
    }
    sort(a + 1, a + 1 + n, [](PII a, PII b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });
    for (int i = 1; i <= n && c > 0; i++) {
        ll t = ceil(a[i].first, k) - 1;
        ans -= min(t, 1ll * c) * a[i].second;
        c -= t;
    }
    cout << ans;
    return 0;
}