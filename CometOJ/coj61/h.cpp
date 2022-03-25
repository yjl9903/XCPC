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
const int maxn = 200000 + 5;

int n, a[maxn], dp[maxn][2];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 0;
    dp[1][0] = 1e9;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i - 1][1] + 1;
        if (a[i] > a[i - 1]) dp[i][0] = min(dp[i - 1][0], dp[i][0]);
        dp[i][1] = dp[i - 1][0];
        if (a[i] < a[i - 1]) dp[i][1] = min(dp[i - 1][1], dp[i][1]);
        dbg(dp[i][0], dp[i][1]);
    }
    cout << min(dp[n][0], dp[n][1]);
    return 0;
} 