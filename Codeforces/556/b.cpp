#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, nxt[maxn][26];
char s[maxn];

string reg[maxn];
int dp[255][255][255], len[3];

int main() {
    scanf("%d%d%s", &n, &q, s + 1);
    for (int i = 0; i < 26; i++) nxt[n][i] = nxt[n + 1][i] = n + 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    // dp[0][0][0] = 1;
    char op[2], ch[2]; int tp;
    while (q--) {
        scanf("%s%d", op, &tp); tp--;
        if (op[0] == '+') {
            scanf("%s", ch);
            len[tp]++; reg[tp] += ch[0];
            int x = 0, y = 0, z = 0;
            if (tp == 0) x = len[0];
            if (tp == 1) y = len[1];
            if (tp == 2) z = len[2];
            for (int i = x; i <= len[0]; i++) {
                for (int j = y; j <= len[1]; j++) {
                    for (int k = z; k <= len[2]; k++) {
                        // dp[i][j][k] = nxt[dp[i - 1][j][k]][ch[i] - 'a'];
                        dp[i][j][k] = n + 1;
                        if (i > 0) dp[i][j][k] = min(dp[i][j][k], nxt[dp[i - 1][j][k]][reg[0][i - 1] - 'a']);
                        if (j > 0) dp[i][j][k] = min(dp[i][j][k], nxt[dp[i][j - 1][k]][reg[1][j - 1] - 'a']);
                        if (k > 0) dp[i][j][k] = min(dp[i][j][k], nxt[dp[i][j][k - 1]][reg[2][k - 1] - 'a']);
                    }
                }
            }
        } else {
            len[tp]--; reg[tp].pop_back();
        }
        if (dp[len[0]][len[1]][len[2]] >= n + 1) puts("NO");
        else puts("YES");
    }
    return 0;
}