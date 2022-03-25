#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 500000 + 5;

struct LinearBase {
    static const int maxl = 63;
    ll a[maxl + 5];
    int cnt;
    LinearBase() { cnt = 0; ms(a, 0); }
    void clear() { cnt = 0; ms(a, 0); }
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
} f;

int n;
ll a[maxn], b[maxn];

int main() {
    scanf("%d", &n);
    ll sa = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%I64d%I64d", a + i, b + i);
        sa ^= a[i]; f.insert(a[i] ^ b[i]);
    }
    if (!f.check(sa)) puts("1/1");
    else {
        ll r = 1ll << f.cnt;
        cout << r - 1 << '/' << r << endl;
    }
    return 0; 
}