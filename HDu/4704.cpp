#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const ll mod = 1e9 + 7;

string s;

ll qpow(ll n){
    ll r = 1, a = 2;
    while (n){
        if (n & 1) r = r * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return r;
}

int main(){
    while (cin >> s){
        ll x = 0;
        for (int i = 0; i < s.length(); i++) x = (x * 10 + s[i] - '0') % (mod - 1);
        ll ans = qpow(x) * qpow(mod - 2) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}