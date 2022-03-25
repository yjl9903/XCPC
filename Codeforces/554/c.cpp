#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ll a, b;

ll ceil(ll x, ll y) {
    return x / y + (x % y == 0 ? 0 : 1);
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    cin >> a >> b;
    if (a > b) swap(a, b);
    ll d = b - a;
    vector<ll> v;
    for (ll i = 1; i * i <= d; i++) {
        if (d % i) continue;
        v.push_back(d / i); 
        if (i != d / i) v.push_back(i);
    }
    ll ans = 1e18; ll p = 0;
    for (ll& x: v) {
        ll k = x * ceil(a, x) - a;
        dbg(x, k);
        ll tot = min(ans, (a + k) / gcd(a + k, b + k) * (b + k));
        if (tot < ans) ans = tot, p = k;
    }
    // cout << ans << endl;
    cout << p << endl;
    return 0;
}