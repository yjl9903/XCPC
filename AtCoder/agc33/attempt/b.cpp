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

int n, m, q;
PII st;
char s[maxn], t[maxn];
int dp[maxn][4];

int main() {
    scanf("%d%d%d%d%d%s%s", &n, &m, &q, &st.first, &st.second, s + 1, t + 1);
    dp[0][0] = st.second;
    dp[0][1] = m - st.second + 1;
    dp[0][2] = st.first;
    dp[0][3] = n - st.first + 1;
    dbg(dp[0][0], dp[0][1], dp[0][2], dp[0][3]);
    int flag = 0;
    for (int i = 1; i <= q; i++) {
        int dx = 0, dy = 0;
        if (s[i] == 'L') dy = -1;
        if (s[i] == 'R') dy = 1;
        if (s[i] == 'U') dx = -1;
        if (s[i] == 'D') dx = 1;
        dp[i][0] = min(dp[i - 1][0], dp[i - 1][0] + dy);
        dp[i][1] = min(dp[i - 1][1], dp[i - 1][1] - dy);
        dp[i][2] = min(dp[i - 1][2], dp[i - 1][2] + dx);
        dp[i][3] = min(dp[i - 1][3], dp[i - 1][3] - dx);
        dbg(dp[i][0], dp[i][1], dp[i][2], dp[i][3]);
        for (int j = 0; j < 4; j++) if (dp[i][j] == 0) flag = 1;
        if (flag) break;
        dx = 0; dy = 0;
        if (t[i] == 'L') dy = -1;
        if (t[i] == 'R') dy = 1;
        if (t[i] == 'U') dx = -1;
        if (t[i] == 'D') dx = 1;
        dp[i][0] = max(dp[i][0], dp[i][0] + dy);
        dp[i][1] = max(dp[i][1], dp[i][1] - dy);
        dp[i][2] = max(dp[i][2], dp[i][2] + dx);
        dp[i][3] = max(dp[i][3], dp[i][3] - dx);
    }
    if (flag) puts("NO");
    else puts("YES");
    return 0;
}