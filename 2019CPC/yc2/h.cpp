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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, w[maxn];
char s[maxn], wrong[] = "wrong";
ll dp[maxn][5];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) scanf("%d", w + i);
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0];
        if (s[i] == 'w') dp[i][0] += w[i]; 
        for (int j = 1; j < 5; j++) {
            if (s[i] == wrong[j]) {
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j] + w[i]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
        // for (int j = 0; j < 5; j++) {
        //     dbg(i, j, dp[i][j]);
        // }
    }
    cout << dp[n][4];
    return 0;
}