#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#include <unordered_map>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
const int maxm = 1e6 + 5;

struct fastIO {
    char s[100000]; int it,len;
    fastIO() { it = len = 0; }
    inline char get() {
        if (it < len) return s[it++];
        it = 0; len = fread(s, 1, 100000, stdin);
        if (len == 0) return EOF;
        else return s[it++];
    }
    bool notend() {
        char c = get();
        while(c == ' ' || c == '\n') c = get();
        if (it > 0) it--;
        return c != EOF;
    }
} buff;
inline int gi() {
    int r = 0; bool ng = 0; 
    char c = buff.get();
    while (c != '-' && (c < '0' || c > '9')) c = buff.get();
    if (c == '-') ng = 1, c = buff.get();
    while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
    return ng ? -r : r;
}

int n, nn, m, a[maxn];

int tot, root[maxn], cnt[maxm * 40], ls[maxm * 40], rs[maxm * 40];
void update(int p, int x, int pre, int l, int r, int &rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre];
    cnt[rt] = cnt[pre] + x;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (p <= m) update(p, x, ls[pre], lson);
    else update(p, x, rs[pre], rson);
}
int queryeq(int p, int pre, int l, int r, int rt) {
    if (l == r) return cnt[rt] - cnt[pre];
    int m = (l + r) / 2;
    if (p <= m) return queryeq(p, ls[pre], lson);
    else return queryeq(p, rs[pre], rson);
}
int queryls(int p, int pre, int l, int r, int rt) {
    if (l == r) return cnt[rt] - cnt[pre];
    int m = (l + r) / 2;
    if (p <= m) return queryls(p, ls[pre], lson);
    else return (cnt[rt] - cnt[pre]) - (cnt[rs[rt]] - cnt[rs[pre]]) + queryls(p, rs[pre], rson);
}
int query(int k, int pre, int l, int r, int rt) {
    if (l == r) return l;
    int m = (l + r) >> 1, s = cnt[ls[rt]] - cnt[ls[pre]];
    if (k <= s) return query(k, ls[pre], lson);
    else return query(k - s, rs[pre], rson);
}

int lll, rr;
int kth(int k) {
    return query(k, root[lll - 1], 1, nn, root[rr]);
}

int main() {
    int T = gi();
    while (T--) {
        tot = 0;
        n = gi(); m = gi();
        nn = 0;
        for (int i = 1; i <= n; i++) a[i] = gi(), nn = max(nn, a[i]);
        for (int i = 1; i <= n; i++) {
            update(a[i], 1, root[i - 1], 1, nn, root[i]);
        }

        int last = 0, l, r, p, k;
        while (m--) {
            l = gi(); r = gi(); p = gi(); k = gi();
            l ^= last; r ^= last; p ^= last; k ^= last;
            lll = l; rr = r;

            int len = r - l + 1, len1, len2, i, j;
            if (p <= nn) {
                int c1 = queryeq(p, root[l - 1], 1, nn, root[r]);
                if (k <= c1) {
                    printf("%d\n", last = 0); continue;
                }
                k -= c1;
                len1 = queryls(p, root[l - 1], 1, nn, root[r]) - c1;
                len2 = len - len1 - c1;
                i = len1;
                j = len1 + c1 + 1;
            } else {
                len1 = len;
                len2 = 0;
                i = len;
                j = len + 1;
            }

            // int len1 = queryls(p, root[l - 1], 1, nn, root[r]) - c1;
            // int len2 = len - len1 - c1;
            //dbg(len1, c1, len2);
            // int i = len1, j = len1 + c1 + 1;

            // auto kth = [&](int k) -> int {
            //     return query(k, root[l - 1], 1, nn, root[r]);
            // };
            
            k--;
            int lasti = -10, lastj = -10, qi, qj;
            while (k--) {
                if (i >= 1 && j <= len) {
                    int a, b;
                    if (i == lasti) a = qi;
                    else lasti = i, a = qi = kth(i);
                    if (j == lastj) b = qj;
                    else lastj = j, b = qj = kth(j);
                    if (p - a < b - p) i--;
                    else j++;
                } else if (i >= 1) i--;
                else if (j <= len) j++;
            }

            int ans = -1;
            if (i >= 1 && j <= len) {
                int a = kth(i), b = kth(j);
                if (p - a < b - p) ans = p - a;
                else ans = b - p;
            } else if (i >= 1) ans = p - kth(i);
            else if (j <= len) ans = kth(j) - p;

            assert(ans != -1);
            printf("%d\n", last = ans);
        }
    }
    return 0;
}