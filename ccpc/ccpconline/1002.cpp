#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

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

int n, q, a[maxn], vis[maxn];

int mx[maxn << 2];
void pushup(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    if (l == r) {
        mx[rt] = vis[l];
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int l, int r, int rt) {
    if (l == r) {
        mx[rt] = n + 1;
        return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, lson);
    else update(i, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return mx[rt];
    int m = (l + r) / 2, ans = 0;
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
}

int main() {
    // int T; scanf("%d", &T);
    int T = gi();
    while (T--) {
        // scanf("%d%d", &n, &q);
        n = gi(); q = gi();
        // for (int i = 1; i <= n; i++) scanf("%d", a + i), vis[a[i]] = i;
        for (int i = 1; i <= n; i++) a[i] = gi(), vis[a[i]] = i;
        build(1, n, 1);
        int last = 0, op, pos, r, k;
        while (q--) {
            // scanf("%d", &op);
            op = gi();
            if (op == 1) {
                // scanf("%d", &pos);
                pos = gi();
                pos ^= last;
                // dbg(pos);
                update(a[pos], 1, n, 1);
            } else {
                // scanf("%d%d", &r, &k);
                r = gi(); k = gi();
                r ^= last; k ^= last;
                int tl = k, tr = n, ans = k;
                while (tl <= tr) {
                    int m = (tl + tr) / 2;
                    if (query(k, m, 1, n, 1) <= r) ans = m + 1, tl = m + 1;
                    else tr = m - 1;
                }
                // dbg(r, k, ans);
                printf("%d\n", last = ans);
            }
        }
    }
    return 0;
}