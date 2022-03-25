#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

int x; ll n;

int cal(int p) {
    ll r = 0, x = p;
    while (x <= n) {
        r += n / x;
        if (n / x < p) break;
        x = x * p;
    }
    return qpow(p, r % (mod - 1));
}

int main() {
    scanf("%d%lld", &x, &n);
    int ans = 1;
    for (int i = 2; 1ll * i * i <= x; i++) {
        if (x % i) continue;
        while (x % i == 0) x /= i;
        ans = mul(ans, cal(i));
    }
    if (x > 1) ans = mul(ans, cal(x));
    cout << ans;
    return 0;
}