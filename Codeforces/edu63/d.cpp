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
const int maxn = 300000 + 5;

int n, x;
ll a[maxn], dp[maxn][3];

ll max(ll a, ll b, ll c) {
    return max(a, max(b, c));
}

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
    ll mx = 0;
    for (int i = n; i >= 1; i--) {
        dp[i][0] = max(a[i], a[i] + max(dp[i + 1][0], dp[i + 1][1], dp[i + 1][2]));
        dp[i][1] = max(1ll * x * a[i], 1ll * x * a[i] + max(dp[i + 1][1], dp[i + 1][2]));
        // dp[i][1] = max(1ll)
        dp[i][2] = max(a[i], a[i] + dp[i + 1][2]);
        dbg(dp[i][0], dp[i][1], dp[i][2]);
        mx = max(dp[i][0], mx);
        mx = max(dp[i][1], mx);
        mx = max(dp[i][2], mx);
    }
    cout << mx << endl;
    return 0;
}