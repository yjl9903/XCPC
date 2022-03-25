#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn]; ll m, b[maxn];

inline ll ceil(ll x, ll y){ return x % y == 0 ? x / y : x / y + 1; }
bool check(ll x){
    for (int i = 1; i <= n; i++) b[i] = ceil(x, a[i]);
    ll ans = 1; b[1]--;
    for (int i = 1; i < n; i++){
        ans += 2 * b[i] + 1;
        if (i == n - 1){
            if (b[i + 1] <= b[i]) ans--;
            else ans += 2 * (b[i + 1] - b[i] - 1);
        }
        if (ans > m) return 0;
        b[i + 1] = max(0ll, b[i + 1] - b[i] - 1);
    }
    return ans <= m;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%lld", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        ll l = 0, r = 1e13, ans = 0;
        while (l <= r){
            ll m = (l + r) / 2;
            if (check(m)) ans = m, l = m + 1;
            else r = m - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}