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

namespace manacher {
    char s[maxn << 1] = "##";
    int n, hw[maxn << 1];
    void init(char a[]) {
        int i;
        for (i = 1; a[i]; i++) {
            s[i * 2] = a[i];
            s[i * 2 + 1] = '#';
        }
        n = i * 2 + 2; s[n] = 0;
    }
    void manacher() {
        int maxr = 0, m = 0;
        for (int i = 1; i < n; i++) {
            if (i < maxr) hw[i] = min(hw[m * 2 - i], hw[m] + m - i);
            else hw[i] = 1;
            while (s[i + hw[i]] == s[i - hw[i]]) hw[i]++;
            if (hw[i] + i > maxr) {
                m = i; maxr = hw[i] + i;
            }
        }
    }
    int build(char s[]) {
        init(s); manacher();
    }
    int check(int l, int r) {
        int mid = (l + r);
        if (hw[mid] >= mid - 2 * l + 1) return 1;
        else return 0;
    }
}
using manacher::check;

namespace pam {
    int sz, tot, last;
    int cnt[maxn], pos[maxn], ch[maxn][26], len[maxn], fail[maxn];
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
            pos[x] = tot;
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            ch[now][c - 'a'] = x;
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
    }
    void count(ll ans[]) {
        for (int i = sz; i >= 0; i--) {
            cnt[fail[i]] += cnt[i];
        }
        for (int i = 2; i <= sz; i++) {
            int r = pos[i], l = pos[i] - len[i] + 1;
            if (check(l, (l + r) / 2)) ans[len[i]] += cnt[i];
        }
    }
}

char s[maxn];
ll ans[maxn];

int main() {
    while (scanf("%s", s + 1) == 1) {
        pam::clear();
        manacher::build(s);
        int n = strlen(s + 1);
        for (int i = 1; i <= n; i++) {
            pam::insert(s[i]); ans[i] = 0;
        }
        pam::count(ans);
        for (int i = 1; i <= n; i++) {
            printf("%lld%c", ans[i], " \n"[i == n]);
        }
    }
    return 0;
}