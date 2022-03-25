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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 30 + 5;
const int maxs = 1 << 26;

int n, m, g[maxn];
char dp[maxs + 5];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) g[i] |= 1 << i;
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        g[u] |= 1 << v;
        g[v] |= 1 << u;
    }
    int ans = 0, ss = 1 << n;
    auto gmax = [&](int a, int b) -> int {
        if (a > b) return a;
        else return b;
    };
    for (int s = 1; s < ss; s++) {
        int lb = s & -s, pos = __builtin_ctz(lb);
        dp[s] = gmax(dp[s ^ lb], 1 + dp[s & (~g[pos])]);
        ans += dp[s];
    }
    cout << ans;
    return 0;
}