#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

char s[maxn], t[maxn], p[maxn];
int slen, tlen, plen, nxt[maxn][26], vis[maxn], cnt[26];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        ms(vis, 0); ms(cnt, 0);
        scanf("%s%s%s", s + 1, t + 1, p + 1);
        slen = strlen(s + 1);
        tlen = strlen(t + 1);
        plen = strlen(p + 1);
        for (int i = 0; i < 26; i++) nxt[tlen + 1][i] = nxt[tlen][i] = tlen + 1;
        for (int i = tlen - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
            nxt[i][t[i + 1] - 'a'] = i + 1; 
        }
        int u = 0;
        for (int i = 1; i <= slen; i++) {
            u = nxt[u][s[i] - 'a']; vis[u] = 1;
        }
        if (u == tlen + 1) {
            puts("NO"); continue;
        }
        for (int i = 1; i <= tlen; i++) if (!vis[i]) {
            cnt[t[i] - 'a']++;
        }
        for (int i = 1; i <= plen; i++) {
            cnt[p[i] - 'a']--;
        }
        int f = 1;
        for (int i = 0; i < 26; i++) if (cnt[i] > 0) f = 0;
        if (f) puts("YES");
        else puts("NO");
    }
    return 0;
}