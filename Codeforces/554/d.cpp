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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

int n;
ll dp[maxn][maxn], a[maxn];

void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

int main() {
    cin >> n;
    dp[1][1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= i; j++) {
            add(a[i + j - 2], dp[i][j]);
        }
    }
    ll ans = 0;
    for (int i = 1; i <= 2 * n; i += 2) add(ans, a[i]);
    cout << ans << endl;
    return 0;
}