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

struct LinearBase {
    static const int maxl = 63;
    ll a[maxl + 5];
    int cnt;
    LinearBase() { cnt=0; ms(a, 0); }
    void clear() { cnt=0; ms(a, 0); }
    int insert(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (a[i]) x ^= a[i];
                else {
                    for (int k = 0; k < i; k++) 
                        if (x & (1ll << k)) x ^= a[k];
                    for (int k = i + 1; k < maxl; k++) 
                        if (a[k] & (1ll << i)) a[k] ^= x;
                    a[i] = x; cnt++;
                    return true;
                }
            }
        }
        return false;
    }
    bool check(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i]) x ^= a[i];
                else return false;
            }
        }
        return true;
    }
} f, g, h;

int n; ll a[maxn], two[maxn];

int main() {
    two[0] = 1;
    for (int i = 1; i < maxn; i++) two[i] = 2ll * two[i - 1] % mod;
    while (scanf("%d", &n) == 1) {
        vector<ll> x, y;
        f.clear(); g.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%lld", a + i);
            if (f.insert(a[i])) x.push_back(a[i]);
            else y.push_back(a[i]);
        }
        ll ans = 0;
        if (f.cnt < n) ans = (n - f.cnt) * two[n - f.cnt - 1] % mod;
        for (ll x: y) g.insert(x);
        for (int i = 0; i < (int)x.size(); i++) {
            ll a = x[i];
            h = g;
            for (int j = 0; j < (int)x.size(); j++) {
                if (i == j) continue;
                h.insert(x[j]);
            }
            if (!h.insert(x[i])) {
                ans = (ans + two[n - h.cnt - 1]) % mod;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}