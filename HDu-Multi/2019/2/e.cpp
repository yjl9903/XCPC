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
const int maxn = 100000 + 5;

namespace pam {
    int sz, tot, last;
    int ch[maxn][26], len[maxn], fail[maxn];
    int cnt[maxn], dep[maxn], half[maxn], val[maxn];
    char s[maxn];
    int node(int l) {
        sz++; ms(ch[sz], 0);
        len[sz] = l; fail[sz] = 0;
        cnt[sz] = dep[sz] = 0;
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

            if (len[x] == 1) half[x] = 1;
            else {
                int pos = half[now];
                while (s[tot - len[pos] - 1] != s[tot] || (2 + len[pos]) * 2 > len[x]) pos = fail[pos];
                half[x] = ch[pos][c - 'a'];
            }
            val[x] = 1;
            if (len[x] / 2 == len[half[x]]) val[x] += val[half[x]];
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
    }
    ll count() {
        for (int i = sz; i >= 0; i--) {
            cnt[fail[i]] += cnt[i];
        }
        ll ans = 0;
        for (int i = 2; i <= sz; i++) {
            ans += 1ll * cnt[i] * val[i];
        }
        return ans;   
    }
}

char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        pam::clear();
        scanf("%s", s + 1);
        for (int i = 1; s[i]; i++) {
            pam::insert(s[i]);
        }
        printf("%lld\n", pam::count());
    }
    return 0;
}