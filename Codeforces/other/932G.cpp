#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1000000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}

namespace pam {
    int sz, tot, last;
    int ch[maxn][26], len[maxn], fail[maxn];
    int cnt[maxn], dep[maxn], dif[maxn], slink[maxn];
    char s[maxn];
    int node(int l) {
        sz++; 
        memset(ch[sz], 0, sizeof(ch[sz]));
        len[sz] = l; 
        fail[sz] = 0;
        cnt[sz] = 0;
        dep[sz] = 0;
        return sz;
    }
    void clear() {
        sz = -1; last = 0;
        s[tot = 0] = '$';
        node(0); node(-1);
        fail[0] = 1;
    }
    int getfail(int x) {
        while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
        return x;
    }
    void insert(char c) {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            dep[x] = dep[fail[x]] + 1;
            ch[now][c - 'a'] = x;

            dif[x] = len[x] - len[fail[x]];
            if (dif[x] == dif[fail[x]]) slink[x] = slink[fail[x]];
            else slink[x] = fail[x];
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
    }
}
using pam::len;
using pam::fail;
using pam::slink;
using pam::dif;

int n, dp[maxn], g[maxn]; char s[maxn], t[maxn];

int main() {
    pam::clear();
    scanf("%s", s + 1); 
    n = strlen(s + 1);
    for (int i = 1, j = 0; i <= n; i++) t[++j] = s[i], t[++j] = s[n - i + 1];
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        pam::insert(t[i]);
        for (int x = pam::last; x > 1; x = slink[x]) {
            g[x] = dp[i - len[slink[x]] - dif[x]];
            if (dif[x] == dif[fail[x]]) g[x] = add(g[x], g[fail[x]]);
            if (i % 2 == 0) dp[i] = add(dp[i], g[x]);
        }
    }
    printf("%d", dp[n]);
    return 0;
}