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
    // last1: right, last2: left
    int sz, last1, last2, l, r;
    int ch[maxn][26], len[maxn], fail[maxn];
    int cnt[maxn], dep[maxn];
    char s[maxn];
    int node(int l) {
        sz++; ms(ch[sz], 0);
        len[sz] = l;
        fail[sz] = cnt[sz] = dep[sz] = 0;
        return sz;
    }
    void clear() {
        sz = -1; last1 = last2 = 0;
        l = 100002; r = l - 1;
        node(0); node(-1);
        fail[0] = 1;
        ms(s, -1);
    }
    int getfail1(int x) {
        while (s[r - len[x] - 1] != s[r]) x = fail[x];
        return x;
    }
    int getfail2(int x) {
        while (s[l + len[x] + 1] != s[l]) x = fail[x];
        return x;
    }
    int insertR(char c) {
        s[++r] = c;
        int now = getfail1(last1);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail1(fail[now])][c - 'a'];
            dep[x] = dep[fail[x]] + 1;
            ch[now][c - 'a'] = x;
        }
        last1 = ch[now][c - 'a'];
        cnt[last1]++;
        if (len[last1] == r - l + 1) last2 = last1;
        return dep[last1];
    }
    int insertL(char c) {
        s[--l] = c;
        int now = getfail2(last2);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail2(fail[now])][c - 'a'];
            dep[x] = dep[fail[x]] + 1;
            ch[now][c - 'a'] = x;
        }
        last2 = ch[now][c - 'a'];
        cnt[last2]++;
        if (len[last2] == r - l + 1) last1 = last2;
        return dep[last2];
    }
}

int q;

int main() {
    while (scanf("%d", &q) == 1) {
        pam::clear();
        int op; ll pre = 0; char s[2];
        while (q--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%s", s);
                pre += pam::insertL(s[0]);
            } else if (op == 2) {
                scanf("%s", s);
                pre += pam::insertR(s[0]);
            } else if (op == 3) {
                printf("%d\n", pam::sz - 1);
            } else if (op == 4) {
                printf("%lld\n", pre);
            }
        }
    }
    return 0;
}