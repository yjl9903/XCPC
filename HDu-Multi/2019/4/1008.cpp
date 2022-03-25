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
int queryls(int p, int pre, int l, int r, int rt) {
    if (l == r) return cnt[rt] - cnt[pre];
    int m = (l + r) / 2;
    if (p <= m) return queryls(p, ls[pre], lson);
    else return (cnt[rt] - cnt[pre]) - (cnt[rs[rt]] - cnt[rs[pre]]) + queryls(p, rs[pre], rson);
}

int lll, rr;
int check(int l, int r) {
    r = min(r, nn);
    int sum1 = queryls(r, root[lll - 1], 1, nn, root[rr]);
    if (l <= 1) return sum1;
    int sum2 = queryls(l - 1, root[lll - 1], 1, nn, root[rr]);
    return sum1 - sum2;
}
int cal(int p, int k) {
    int l = 0, r = nn, ans = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(p - m, p + m) < k) ans = m + 1, l = m + 1;
        else r = m - 1;
    }
    return ans;
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
            printf("%d\n", last = cal(p, k));
        }
    }
    return 0;
}