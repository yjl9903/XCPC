#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, k, A, B, pos[maxn];

int cal(ll l, ll r) {
    int k1 = lower_bound(pos, pos + k, l) - pos;
    int k2 = upper_bound(pos, pos + k, r) - pos;
    return k2 - k1;
}

ll solve(ll l, ll r) {
    // cout << l << ' ' << r <<endl;
    if (l >= r) {
        int cnt = cal(l, r);
        if (cnt) return 1ll * B * cnt;
        else return A;
    }
    int cnt = cal(l, r);
    ll tot;
    if (cnt) tot = 1ll * B * cnt * (r - l + 1);
    else return A;
    ll m = (l + r) / 2;
    // cout << l << ' ' << r << endl;
    return min(tot, solve(l, m) + solve(m + 1, r));
}

int main() {
    scanf("%d%d%d%d", &n, &k, &A, &B);
    for (int i = 0; i < k; i++) scanf("%d", pos + i);
    sort(pos, pos + k);
    cout << solve(1, 1 << n) << endl;
    return 0;
}