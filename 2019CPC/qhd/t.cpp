#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <ctime>
#include <cstdlib>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace Pollard_Rho {
    inline ll gcd(ll a, ll b) {
        #define ctz __builtin_ctzll
        int shift = ctz(a | b);
        b >>= ctz(b);
        while (a) {
            a >>= ctz(a);
            if (a < b) swap(a, b);
            a -= b;
        }
        return b << shift;
    }
    inline ll mulmod(ll x, ll y, const ll z) {
        return (x * y - (ll)(((long double)x * y + 0.5) / (long double)z) * z + z) % z;
    }
    inline ll powmod(ll a, ll b, const ll mo) {
        ll s = 1;
        for (; b; b >>= 1, a = mulmod(a, a, mo))
            if (b & 1) s = mulmod(s, a, mo);
        return s;
    }
    bool isPrime(ll p) { // Miller-Rabin
        const vector<int> a = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
        const int lena = (int)a.size();
        if (p == 2) return true;
        if (p == 1 || !(p & 1)) return false;
        ll D = p - 1;
        while (!(D & 1)) D >>= 1;
        for (int i = 0; i < lena && a[i] < p; i++) {
            ll d = D, t = powmod(a[i], d, p);
            if (t == 1) continue;
            for (; d != p - 1 && t != p - 1; d <<= 1) t = mulmod(t, t, p);
            if (d == p - 1) return false;
        }
        return true;
    }

    ll facs[70]; int pfacs;
    void reportFactor(ll n) { // 得到一个素因子
        facs[pfacs++] = n;
    }
    void getFactor(ll n) { // Pollard-Rho
        if (n == 1) return ;
        if (isPrime(n)) { 
            reportFactor(n); 
            return ; 
        }
        while (true) {
            ll c = rand() % n, i = 1, x = rand() % n, y = x, k = 2;
            do {
                ll d = gcd(n + y - x, n);
                if (d != 1 && d != n) {
                    getFactor(d);
                    getFactor(n / d);
                    return ;
                }
                if (++i == k) y = x, k <<= 1;
                x = (mulmod(x, x, n) + c) % n;
            } while (y != x);
        }
    }

    vector<ll> factor(ll n) {
        pfacs = 0; getFactor(n);
        vector<ll> v;
        for (int i = 0; i < pfacs; i++) v.push_back(facs[i]);
        sort(v.begin(), v.end());
        return v;
    }
}

int main() {
    srand(time(0));
    int T; scanf("%d",&T);
    ll n, m;
    while (T--) {
        scanf("%lld",&n);
        if (Pollard_Rho::isPrime(n)) {
            printf("Prime\n");
        } else {
            vector<ll> ans = Pollard_Rho::factor(n);
            for (int i = 0; i < (int)ans.size(); i++) {
                printf("%lld%c", ans[i], i == (int)ans.size() - 1? '\n' : ' ');
            }
        }
    }
    return 0;
}