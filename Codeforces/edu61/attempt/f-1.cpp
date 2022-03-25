#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
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
const int mod = 998244353;
const int maxn = 500 + 5;

int n, c[maxn], len, pre[maxn][26];

char a[maxn];

int f[maxn][maxn][30];
int dp(int l, int r, int c) {
    if (f[l][r][c] != -1) return f[l][r][c];
    // dbg(l, r);
    if (l > r) return 0;
    if (l == r) return a[l] != c + 'a';
    
    int last = l, ans = 0;
    for (int i = l; i <= r; i++) {
        if ((int)a[i] == c + 'a') {
            int tot = 1e9;
            for (int k = 0; k < 26; k++) if (pre[i - 1][k] - pre[last - 1][k] > 0) 
                tot = min(tot, dp(last, i - 1, k) + (k != c));
            if (last >= i) tot = 0;
            // dbg(last, i, tot);
            ans += tot;
            last = i + 1;
        }
    }
    // dbg(l, r, ans);
    if (last > r) return ans;
    int tot = 1e9;
    for (int k = 0; k < 26; k++) if (pre[r][k] - pre[last - 1][k] > 0)
        tot = min(tot, dp(last, r, k) + (k != c));
    return f[l][r][c] = ans + tot;
}

int main() {
    ms(f, -1);
    scanf("%d%s", &n, a + 1);
    for (int i = 1; i <= n; i++) {
        pre[i][a[i] - 'a']++;
        for (int j = 0; j < 26; j++) pre[i][j] += pre[i - 1][j];
    }
    int ans = 1e9;
    // cout << dp(1, n, 0) << endl;
    for (int i = 0; i < 26; i++) if (pre[n][i]) {
        dbg(dp(1, n, i), i);
        ans = min(ans, dp(1, n, i) + 1);
    }
    cout << ans << endl;
    return 0;
}