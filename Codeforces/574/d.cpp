#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int n;
ll y[20];
string a[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; reverse(a[i].begin(), a[i].end());
    }
    for (int i = 0; i <= 11; i++) {
        for (int j = 1; j <= n; j++) {
            y[i] += qpow(10, min((int)a[j].length(), i));
        }
        y[i] %= mod;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)a[i].length(); j++) {
            ll tot = y[j + 1];
            if (j) tot += y[j];
            else tot += n;
            ans = (ans + (a[i][j] - '0') * qpow(10, j) * tot % mod) % mod;
        }
    }
    cout << ans;
    return 0;
}