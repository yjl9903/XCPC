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
    int cnt[maxn], ch[maxn][26], len[maxn], fail[maxn];
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
    int insert(char c) {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            ch[now][c - 'a'] = x;
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
        return len[last];
    }
}

char s[maxn];
int n, pre[maxn];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    pam::clear();
    for (int i = 1; i <= n; i++) {
        pre[i] = pam::insert(s[i]);
    }
    pam::clear();
    int ans = 0;
    for (int i = n; i >= 2; i--) {
        ans = max(ans, pre[i - 1] + pam::insert(s[i]));
    }
    cout << ans;
    return 0;
}