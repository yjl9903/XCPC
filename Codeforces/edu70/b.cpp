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
const int inf = 1 << 20;
const int maxn = 4000000 + 5;

int n;
char s[maxn];

int dp[20][20], res[20][20];
int check(int x, int y) {
    if (x > y) return res[y][x];
    for (int i = 0; i < 10; i++) for (int j = 0; j < 10; j++) dp[i][j] = inf;
    for (int i = 0; i < 10; i++) {
        // dp[i][i] = 0;
        dp[i][(i + x) % 10] = dp[i][(i + y) % 10] = 1;
    }
    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                }
            }
        }
    }
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        int cost = dp[s[i - 1] - '0'][s[i] - '0'];
        if (cost == inf) return res[x][y] = -1;
        if (cost) ans += cost - 1;
    }
    return res[x][y] = ans;
}

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", check(i, j));
        }
        puts("");
    }
    return 0;
}