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
const int mod = 19260817;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

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

int n, m;
string mp[maxn];
vector<int> dp1[maxn], dp2[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> mp[i];
        dp1[i].resize(m);
        dp2[i].resize(m);
    }
    dp1[0][0] = 1;
    dp2[n - 1][m - 1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i == 0; j < m; j++) {
            if (mp[i][j] == '#') continue;
            if (i > 0) dp1[i][j] = dp1[i - 1][j];
            if (j > 0) dp1[i][j] = add(dp1[i][j], dp1[i][j - 1]);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i == n - 1 ? m - 2 : m - 1; j >= 0; j--) {
            if (mp[i][j] == '#') continue;
            if (i + 1 < n) dp2[i][j] = dp2[i + 1][j];
            if (j + 1 < m) dp2[i][j] = add(dp2[i][j], dp2[i][j + 1]);
        }
    }
    if (dp1[n - 1][m - 1] == 0) return puts("0"), 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == '#') continue;
            if (i == 0 && j == 0) continue;
            if (i == n - 1 && j == m - 1) continue;
            int tot = mul(dp1[i][j], dp2[i][j]);
            if (tot == dp1[n - 1][m - 1]) {
                puts("1"); return 0;
            }
        }
    }
    puts("2");
    return 0;
}