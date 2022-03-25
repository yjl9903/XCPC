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
const int maxn = 300000 + 5;

namespace pam {
    int sz, tot, last;
    int ch[maxn][26], len[maxn], fail[maxn];
    int cnt[maxn], dep[maxn];
    char s[maxn];
    int node(int l) {
        sz++; ms(ch[sz], 0);
        len[sz] = l; fail[sz] = cnt[sz] = 0;
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
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
    }
    ll count() {
        ll ans = 0;
        for (int i = sz; i >= 0; i--) {
            cnt[fail[i]] += cnt[i];
        }
        for (int i = 1; i <= sz; i++) {
            ans = max(ans, 1ll * len[i] * cnt[i]);
        }
        return ans;
    }
}

char s[maxn];

int main() {
    pam::clear();
    scanf("%s", s + 1);
    for (int i = 1; s[i]; i++) {
        pam::insert(s[i]);
        if (i > 1) putchar(' ');
        printf("%d", pam::sz - 1);
    }
    // cout << pam::count();
    return 0;
}