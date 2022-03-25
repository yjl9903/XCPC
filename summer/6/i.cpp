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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, a[maxn], vis[maxn];

int cnt, ls[maxn * 40], rs[maxn * 40], tree[maxn * 40], root[maxn];
void update(int i, int x, int pre, int l, int r, int& rt) {
    rt = ++cnt; ls[rt] = ls[pre]; rs[rt] = rs[pre]; tree[rt] = tree[pre] + x;
    if (l == r) {
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
int query(int p, int l, int r, int rt){
    if (p == r) return tree[rt];
    int m = (l + r) >> 1;
    if (p <= m) return query(p, lson);
    else return query(p, rson) + tree[ls[rt]];
}
int kth(int k, int l, int r, int rt){
    if (l == r) return l;
    int m = (l + r) >> 1, s = tree[ls[rt]];
    if (k <= s) return kth(k, lson);
    else return kth(k - s, rson);
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        cnt = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = n; i >= 1; i--) {
            if (vis[a[i]]) {
                int tmp;
                update(vis[a[i]], -1, root[i + 1], 1, n, tmp);
                update(i, 1, tmp, 1, n, root[i]);
            } else {
                update(i, 1, root[i + 1], 1, n, root[i]);
            }
            vis[a[i]] = i;
        }
        printf("Case #%d:", ++kase);
        int last = 0;
        for (int i = 1, l, r; i <= m; i++) {
            scanf("%d%d", &l, &r);
            int a = (l + last) % n, b = (r + last) % n;
            l = min(a, b) + 1; r = max(a, b) + 1;
            int sum = query(r, 1, n, root[l]);
            int k = sum / 2; if (sum % 2) k++;
            last = kth(k, 1, n, root[l]);
            printf(" %d", last);
        }
        puts("");
        for (int i = 1; i <= n; i++) vis[a[i]] = 0;
    }
    return 0;
}