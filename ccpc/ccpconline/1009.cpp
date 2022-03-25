#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int mod = 998244353;
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

int n, m, C[100][100], f[100];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &mod);
        C[1][0] = C[1][1] = C[0][0] = 1;
        f[0] = f[1] = 1;
        for (int i = 2; i < 100; i++) {
            f[i] = mul(f[i - 1], i);
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++) {
                C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
            }
        }
        int ans = 0;
        for (int i = 1; i <= max(n, m); i++) {
            int tot = mul(qpow(2, n * m - i * i), mul(C[n - 1][i - 1], C[m - 1][i - 1]));
            // if (i > 1) tot = mul(tot, (i - 1) * (i - 1));
            tot = mul(tot, mul(f[i - 1], f[i - 1]));
            ans = add(ans, mul(tot, 2 * i - 1));
        }
        ans = mul(ans, qpow(inv(2), n * m));
        printf("%d\n", ans);
    }
    return 0;
}