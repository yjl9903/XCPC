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

int n, k, a[maxn], id[maxn], ans[maxn];

int b[maxn * 4], tag[maxn * 4];
void build(int l, int r, int rt) {
    b[rt] = tag[rt] = 0;
    if (l == r) {
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
}
void pushdown(int rt) {
    if (tag[rt]) {
        b[rt << 1] = tag[rt];
        b[rt << 1 | 1] = tag[rt];
        tag[rt << 1] = tag[rt];
        tag[rt << 1 | 1] = tag[rt];
        tag[rt] = 0;
    }
}
void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
        b[rt] = tag[rt] = x;
        return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    b[rt] = max(b[rt << 1], b[rt << 1 | 1]);
}
int query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) return b[rt];
    int m = (l + r) / 2, ans = 0;
    pushdown(rt);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            id[a[i]] = i;
        }
        build(1, n, 1);
        ans[1] = 1;
        update(id[1], id[1], 1);
        for (int i = 2; i <= n; i++) {
            int tl = max(1, id[i] - k), tr = min(n, id[i] + k);
            int tot = query(tl, tr);
            // dbg(tl, tr, tot);
            if (tot == 0) ans[i] = 1;
            else {
                ans[i] = 1 + ans[tot];
            }
            update(id[i], id[i], i);
        }
        for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}