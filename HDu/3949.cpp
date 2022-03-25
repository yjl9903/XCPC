#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, m;

struct LinearBase {
    static const int maxl = 63;
    ll a[maxl];
    int cnt;
    LinearBase() { cnt=0; ms(a, 0); }
    void clear() { cnt=0; ms(a, 0); }
    void insert(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x & (1ll << i)){
                if (a[i]) x ^= a[i];
                else {
                    for (int k = 0; k < i; k++) if (x & (1ll << k)) x ^= a[k];
                    for (int k = i + 1; k <= maxl; k++) if (a[k] & (1ll << i)) a[k] ^= x;
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
    #define QUERY_KTH
    #ifdef QUERY_KTH
    vector<ll> v;
    void init_kth() {
        v.clear();
        for (int i = 0; i < maxl; i++) if (a[i]) v.push_back(a[i]);
    }
    ll query(ll k){
        if (v.size() != n) k--;
        if (k >= (1ll << v.size())) return -1;
        ll ans = 0;
        for (int i = 0; i < v.size(); i++) if (k & (1ll << i)){
            ans ^= v[i];
        }
        return ans;
    }
    #endif
} f;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        f.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            ll x; scanf("%lld", &x);
            f.insert(x);
        }
        f.init_kth();
        scanf("%d", &m);
        printf("Case #%d:\n", ++kase);
        while (m--){
            ll x; scanf("%lld", &x);
            printf("%lld\n", f.query(x));
        }
    }
    return 0;
}