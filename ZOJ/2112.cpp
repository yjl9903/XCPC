#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <assert.h>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 50000 + 5;

struct Ope {
    int tp, l, r, k;
    Ope(int ll, int rr, int kk) {
        tp = 1; l = ll; r = rr; k = kk;
    }
    Ope(int i, int t) {
        tp = 2; l = i; k = t;
    }
    Ope() { tp = l = r = k = 0; }
} q[maxn];

int n, nn, m, a[maxn];

vector<int> lsh;
inline void init() {
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = lsh.size();
}
inline int gid(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

int tot, root[maxn], ls[maxn * 600], rs[maxn * 600], cnt[maxn * 600];
void update(int i, int x, int pre, int l, int r, int& rt) {
    rt = ++tot; 
    ls[rt] = ls[pre]; rs[rt] = rs[pre]; cnt[rt] = cnt[pre] + x;
    if (l == r) return ;
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
int L[50], R[50], sl, sr;
int query(int k, int l, int r, int rt) {
    if (l == r) return l;
    int m = (l + r) >> 1, sum = 0;
    for (int i = 1; i <= sl; i++) sum -= cnt[ls[L[i]]];
    for (int i = 1; i <= sr; i++) sum += cnt[ls[R[i]]];
    // dbg(k, l, r, sum);
    if (k <= sum) {
        for (int i = 1; i <= sl; i++) L[i] = ls[L[i]];
        for (int i = 1; i <= sr; i++) R[i] = ls[R[i]];
        return query(k, l, m, 1);
    } else {
        for (int i = 1; i <= sl; i++) L[i] = rs[L[i]];
        for (int i = 1; i <= sr; i++) R[i] = rs[R[i]];
        return query(k - sum, m + 1, r, 1);
    }
}
inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    // int p = gid(a[i]);
    int p = a[i];
    for (; i <= n; i += lowbit(i)) update(p, x, root[i], 1, nn, root[i]);
}
inline int query(int l, int r, int k) {
    sl = sr = 0;
    for (int i = l - 1; i > 0; i -= lowbit(i)) L[++sl] = root[i];
    for (int i = r; i > 0; i -= lowbit(i)) R[++sr] = root[i];
    return lsh[query(k, 1, nn, 1) - 1];
}

char op[5];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        lsh.clear(); tot = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), lsh.push_back(a[i]);
        for (int i = 1, l, r, k; i <= m; i++) {
            scanf("%s", op);
            if (op[0] == 'Q') {
                scanf("%d%d%d", &l, &r, &k);
                q[i] = Ope(l, r, k);
            }
            if (op[0] == 'C') {
                scanf("%d%d", &l, &k);
                q[i] = Ope(l, k);
                lsh.push_back(k);
            }
        }
        init(); 
        for (int i = 1; i <= n; i++) a[i] = gid(a[i]);
        for (int i = 1; i <= n; i++) update(i, 1);
        for (int i = 1; i <= m; i++) {
            if (q[i].tp == 1) {
                printf("%d\n", query(q[i].l, q[i].r, q[i].k));
            }
            if (q[i].tp == 2) {
                int id = q[i].l;
                update(id, -1);
                a[id] = gid(q[i].k);
                update(id, 1);
            }
        }
        for (int i = 1; i <= tot; i++) cnt[i] = ls[i] = rs[i] = 0;
    }
    return 0;
}