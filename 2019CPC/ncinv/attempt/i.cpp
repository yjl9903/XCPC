#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, a[maxn];
ll pre[maxn];

ll solve(int l, int r) {
    if (l == r) return 1ll * a[l] * a[l];
    if (l > r) return 0;
    int m = (l + r) / 2;
    ll r1 = solve(l, m), r2 = solve(m + 1, r);
    ll r3 = a[m] * a[m], r4 = a[m] * a[m];

    int mn = a[m]; ll sum = a[m];
    map<int,ll> mp1, mp2; mp1[mn] = mp2[mn] = sum;
    for (int i = m - 1; i >= l; i--) {
        mn = min(a[i], mn);
        sum += a[i];
        if (mp1.count(mn)) mp1[mn] = max(mp1[mn], sum), mp2[mn] = min(mp2[mn], sum);
        else mp1[mn] = sum;
        r3 = max(r3, sum * mn);
    }
    sum = 0; mn = 1e9;
    for (int i = m + 1; i <= r; i++) {
        mn = min(mn, a[i]);
        
    }


    return max(max(r1, r2), max(r3, r4));
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pre[i] = a[i] + pre[i - 1];
    cout << solve(1, n) << endl;
    return 0;
}