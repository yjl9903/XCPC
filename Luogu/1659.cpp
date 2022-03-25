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
const int mod = 19930726;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

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
    void insert(char c) {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
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

int n, sum[maxn]; ll k;
char s[maxn];

int main() {
    scanf("%d%lld%s", &n, &k, s + 1);
    pam::clear();
    for (int i = 1; i <= n; i++) {
        pam::insert(s[i]);
    }
    pam::count();
    for (int i = 2; i <= pam::sz; i++) {
        sum[pam::len[i]] += pam::cnt[i];
    }
    int ans = 1;
    for (int i = n; i >= 1 && k; i--) {
        if (i % 2 == 0) continue;
        ll s = min(k, 1ll * sum[i]);
        ans = mul(ans, qpow(i, s));
        k -= s;
    }
    if (k) puts("-1");
    else cout << ans;
    return 0;
}