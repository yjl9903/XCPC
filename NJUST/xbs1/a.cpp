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
const int maxn = 200000 + 5;

int n, a[maxn];

void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

ll b[maxn];
inline int lowbit(int x) { return x & -x; }
inline void update(int i, ll x) {
    for (; i <= n; i += lowbit(i)) add(b[i], x);
}
inline ll query(int i) {
    ll r = 0;
    for (; i > 0; i -= lowbit(i)) add(r, b[i]);
    return r % mod;
}

vector<int> lsh;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ms(b, 0); lsh.clear();
        for (int i = 1; i <= n; i++) scanf("%d", a + i), lsh.push_back(a[i]);
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
            ll t = query(a[i] - 1) + 1;
            add(ans, t);
            update(a[i], t);
        }
        printf("%lld\n", ans % mod);
    }
    return 0;
}