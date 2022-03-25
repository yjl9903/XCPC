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

struct LinearBase {
    static const int maxl = 63;
    ll a[maxl + 5];
    int cnt;
    LinearBase() { cnt=0; ms(a, 0); }
    void clear() { cnt=0; ms(a, 0); }
    void insert(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (a[i]) x ^= a[i];
                else {
                    for (int k = 0; k < i; k++) 
                        if (x & (1ll << k)) x ^= a[k];
                    for (int k = i + 1; k < maxl; k++) 
                        if (a[k] & (1ll << i)) a[k] ^= x;
                    a[i] = x; cnt++;
                    return ;
                }
            }
        }
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
    ll qmax(int x) {
        ll res = x;
        for(int i = maxl - 1 ; i >= 0; i--) {
            if ((res ^ a[i]) > res) res ^= a[i];
        }
        return res;
    }
} f;

int n, m;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1, x; i <= n; i++) {
            scanf("%d", &x); f.insert(x);
        }
        ll ans = 0;
        for (int i = 0; i < m; i++) {
            if (f.check(i)) ans++;
        }
        ans *= 1ll << (n - f.cnt);
        printf("Case #%d: ", ++kase);
        cout << (1ll << n) - ans << '\n';
        f.clear();
    }
    return 0;
}