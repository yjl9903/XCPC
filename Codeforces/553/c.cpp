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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

void add(ll& x, ll y) {
    x += y; if (x >= y) x -= mod;
}

ll cal(ll x) {
    ll a = 0, b = 0, ans = 0;
    for (int i = 0; i <= 62; i++) {
        ll tot = 1ll << i;
        if (x >= tot) {
            x -= tot;
            if (i % 2) a += tot;
            else b += tot;
        } else {
            if (i % 2) a += x;
            else b += x;
            break;
        }
    }
    // cout << a << ' ' << b;
    a %= mod; b %= mod;
    return (b * b % mod + a * (1 + a) % mod) % mod;
}

ll l, r;

int main() {
    cin >> l >> r;
    // cout << cal(r);
    cout << (cal(r) - cal(l - 1) + mod) % mod;
    return 0;
}