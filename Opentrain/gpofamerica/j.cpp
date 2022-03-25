#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

char s[maxn], t[200];
int slen, tlen, nxt[maxn][26];

int main() {
    scanf("%s%s", s + 1, t + 1);
    slen = strlen(s + 1);
    tlen = strlen(t + 1);
    for (int j = 0; j < 26; j++) nxt[slen][j] = nxt[slen + 1][j] = slen + 1;
    for (int i = slen - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    ll ans = 0;
    for (int i = 1; i <= slen; i++) {
        int u = i - 1, flag = 1;
        for (int j = 1; j <= tlen; j++) {
            if (nxt[u][t[j] - 'a'] > slen) {
                flag = 0; break;
            }
            u = nxt[u][t[j] - 'a'];
        }
        if (flag) {
            ans += slen - u + 1;
        }
    }
    cout << ans;
    return 0;
}