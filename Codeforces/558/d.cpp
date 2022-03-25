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
const int maxn = 1000 + 5;
const int maxm = 50 + 5;

int sn, tn, pn;
char s[maxm], t[maxm], p[maxn]; 

int fail1[maxm], fail2[maxm], nxt1[maxm][26], nxt2[maxm][26];
void getfail(int len, char* s, int fail[], int nxt[][26]) {
    fail[1] = 0;
    for (int i = 2; i <= len; i++) {
        int cur = fail[i - 1];
        while (cur > 0 && s[cur + 1] != s[i])
            cur = fail[cur];
        if (s[cur + 1] == s[i])
            ++cur;
        fail[i] = cur;
    }

    for (int i = 0; i <= len; i++) {
        dbg(i, fail[i]);
        for (int ch = 0; ch < 26; ch++) {
            int tot = i;
            while (tot && s[tot + 1] != ch + 'a') tot = fail[tot];
            if (s[tot + 1] == ch + 'a') tot++;
            nxt[i][ch] = tot;
            // dbg(i, ch, nxt[i][ch]);
        }
    }
}

int dp[maxn][maxm][maxm];
void update(int f[][maxm], int g[][maxm], char ch) {
    for (int i = 0; i <= sn; i++) {
        for (int j = 0; j <= tn; j++) {
            // if (g[i][j] == -inf) continue;
            // dbg(i, j, g[i][j]);
            for (int c = 0; c < 26; c++) {
                if (ch != '*' && c + 'a' != ch) continue;
                int nxs = nxt1[i][c], nxt = nxt2[j][c];
                f[nxs][nxt] = max(f[nxs][nxt], g[i][j] + (nxs == sn) - (nxt == tn));
                // dbg(nxs, nxt, f[nxs][nxt]);
            }
        }
    }
}

int main() {
    scanf("%s%s%s", p + 1, s + 1, t + 1);
    pn = strlen(p + 1); sn = strlen(s + 1); tn = strlen(t + 1);
    getfail(sn, s, fail1, nxt1);
    getfail(tn, t, fail2, nxt2);
    for (int i = 0; i <= pn; i++) for (int j = 0; j <= sn; j++) for (int k = 0; k <= tn; k++) dp[i][j][k] = -inf;
    dp[0][0][0] = 0;
    for (int i = 1; i <= pn; i++) {
        // dbg(i);
        update(dp[i], dp[i - 1], p[i]);
    }
    int ans = -inf;
    for (int i = 0; i <= sn; i++) for (int j = 0; j <= tn; j++) ans = max(ans, dp[pn][i][j]);
    cout << ans;
    return 0;
}