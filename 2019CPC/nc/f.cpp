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
const int maxn = 400000 + 5;

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

int l, k, n, m, a[100], pre[maxn];
char s[maxn];

namespace sam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        tot = last = 1; ms(ch[1], 0);
    }
    int insert(int c) {
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
}
using namespace sam;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d%s", &l, &k, &n, &m, s + 1);
        for (int i = 0; i <= k; i++) scanf("%d", a + i);
        for (int i = 1; i <= l + m; i++) {
            int x = 1, sum = 0;
            for (int j = 0; j <= k; j++) {
                sum = add(sum, mul(a[j], x));
                x = mul(x, i);
            }
            sum = mul(sum, n - i + 1);
            sum = mul(sum, inv(qpow(26, i)));
            pre[i] = add(pre[i - 1], sum);
        }
        sam::clear();
        int ans = 0;
        auto insert = [&](int c) -> void {
            int u = sam::insert(c);
            int l = len[link[u]], r = len[u];
            ans = add(ans, sub(pre[r], pre[l]));
        };
        for (int i = 1; i <= l; i++) insert(s[i] - 'a');
        printf("%d\n", ans);
        char op[5];
        while (m--) {
            scanf("%s", op);
            insert(op[0] - 'a');
            printf("%d\n", ans);
        }
    }
    return 0;
}