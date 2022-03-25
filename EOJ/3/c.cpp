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
const ll inf = 2e9;
const int maxn = 100000 + 5;

int check(ll t, ll r) {
    ll l = 1;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (m + 1 == t) return 1;
        else if (m + 1 > t) return 0;
        l = m + 1;
    }
    return 0;
}
ll ans = -1;
int dfs(ll l, ll r) {
    if (l > r) return 0;
    if (r > inf) return 0;
    // cout << l << ' ' << r << endl;
    if (check(l, r)) return ans = r, 1;
    if (dfs(l, 2 * r - l)) return 1;
    if (dfs(l, 2 * r - l + 1)) return 1;
    return 0;
}

int l, r;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &l, &r);
        if (l == 1 || l == r) {
            printf("%d\n", r); continue;
        }
        // cout << check(l, r) << endl;
        ans = -1;
        dfs(l, r);
        printf("%d\n", ans);
    }
    return 0;
}