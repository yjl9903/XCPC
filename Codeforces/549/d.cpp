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

ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}

int n, k, a, b;

ll cal(ll st, ll ed) {
    ll l = ed - st;
    if (l <= 0) l += 1ll * n * k;
    ll g = gcd(l, 1ll * n * k);
    return 1ll * n * k / g;
}

int main() {
    cin >> n >> k >> a >> b;
    ll x = 1e18, y = -1e18;
    for (ll i = 1 + b; i <= 1ll * n * k; i += k) {
        // dbg(1 + a, 1 + k - a, i);
        ll p = cal(1 + a, i);
        ll q = cal(1 + k - a, i);
        x = min(min(p, q), x);
        y = max(max(p, q), y);
    }
    for (ll i = 1 + k - b; i <= 1ll * n * k; i += k) {
        ll p = cal(1 + a, i);
        ll q = cal(1 + k - a, i);
        x = min(min(p, q), x);
        y = max(max(p, q), y);
    }
    cout << x << ' ' << y << endl;
    return 0;
}