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
typedef pair<int,ll> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 600000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv(ll x) {
    return qpow(x, mod - 2);
}

int n, nn, a[maxn];
vector<int> lsh;

PII info[maxn];
PII add(PII a, PII b) {
    if (a.first == b.first) return { a.first, (a.second + b.second) % mod };
    else if (a.first > b.first) return a;
    else return b;
}
inline int lowbit(int x) {
    return x & -x;
}
inline void update(int i, PII x) {
    for (; i <= nn; i += lowbit(i)) {
        info[i] = add(info[i], x);
    }
}
inline PII query(int i) {
    PII r = { 0, 1 };
    for (; i; i -= lowbit(i)) {
        r = add(r, info[i]);
    }
    return r;
}

PII pre[maxn], suf[maxn];
ll ans[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = (int)lsh.size();
    for (int i = 1; i <= n; i++) a[i] = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;

    for (int i = 1; i <= n; i++) {
        PII x = query(a[i] - 1);
        pre[i] = x;
        x.first++;
        update(a[i], x);
    }

    PII sum = query(nn);
    int len = sum.first;
    ll fm = inv(sum.second);
    
    for (int i = 1; i <= nn; i++) info[i] = { 0, 0 };
    for (int i = n; i >= 1; i--) {
        a[i] = nn - a[i] + 1;
        PII x = query(a[i] - 1);
        suf[i] = x;
        x.first++;
        update(a[i], x);
    }

    for (int i = 1; i <= n; i++) {
        if (pre[i].first + suf[i].first + 1 == len) {
            ll fz = 1ll * pre[i].second * suf[i].second % mod;
            printf("%lld ", fz * fm % mod);
        } else printf("0 ");
    }
    return 0;
}