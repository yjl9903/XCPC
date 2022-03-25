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
const int maxn = 200000 + 5;

char s[maxn];
int n, ans;

namespace pam {
    int sz, tot, last;
    int ch[maxn][26], len[maxn], fail[maxn];
    int cnt[maxn], dep[maxn];
    char s[maxn];
    int node(int l) {
        sz++; ms(ch[sz], 0);
        len[sz] = l; fail[sz] = cnt[sz] = dep[sz] = 0;
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
    int insert(char c) {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            if (len[x] <= n) ans++;
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            dep[x] = dep[fail[x]] + 1;
            ch[now][c - 'a'] = x;
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
    }
    void count() {
        for (int i = sz; i >= 0; i--) {
            cnt[fail[i]] += cnt[i];
        }
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s + 1);
        pam::clear();
        ans = 0;
        for (int i = 1; i <= n; i++) pam::insert(s[i]);
        for (int i = 1; i <= n; i++) pam::insert(s[i]);
        printf("%d\n", ans);
    }
    return 0;
}