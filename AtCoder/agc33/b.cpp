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
    int x = st.first, y = st.second, flag = 0;
    for (int i = 1; i <= q; i++) {
        if (s[i] == 'L') y--;
        if (y == 0) flag = 1;
        if (t[i] == 'R' && y != m) y++;
    }
    y = st.second;
    for (int i = 1; i <= q; i++) {
        if (s[i] == 'R') y++;
        if (y == m + 1) flag = 1;
        if (t[i] == 'L' && y != 1) y--;
    }
    for (int i = 1; i <= q; i++) {
        if (s[i] == 'U') x--;
        if (x == 0) flag = 1;
        if (t[i] == 'D' && x != n) x++;
    }
    x = st.first;
    for (int i = 1; i <= q; i++) {
        if (s[i] == 'D') x++;
        if (x == n + 1) flag = 1;
        if (t[i] == 'U' && x != 1) x--;
    }
    if (flag) puts("NO");
    else puts("YES");
    return 0;
}
