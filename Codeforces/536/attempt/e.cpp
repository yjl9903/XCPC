#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;
const ll inf = 1e18;

PII tree[maxn << 2], tag[maxn << 2];
void pushup(int rt) {
    tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]);
}
void pushdown(int rt) {
    if (tag[rt].first == 0 && tag[rt].second == 0) return;
    tree[rt << 1] = max(tree[rt << 1], tag[rt]);
    tree[rt << 1 | 1] = max(tree[rt << 1 | 1], tag[rt]);
    tag[rt << 1] = max(tag[rt << 1], tag[rt]);
    tag[rt << 1 | 1] = max(tag[rt << 1 | 1], tag[rt]);
    tag[rt] = make_pair(0, 0);
}
void build(int l, int r, int rt) {
    tag[rt] = tree[rt] = make_pair(0, 0);
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, PII x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        tree[rt] = max(tree[rt], x);
        tag[rt] = max(tag[rt], x);
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
PII query(int p, int l, int r, int rt) {
    if (l == r) return tree[rt];
    int m = (l + r) >> 1;
    pushdown(rt);
    if (p <= m) return query(p, lson);
    else return query(p, rson);
}

int n, m, k, s[maxn], t[maxn], d[maxn], w[maxn];
ll f[300];
int g[300];
PII tt[300];

int main(){
    scanf("%d%d%d", &n, &m, &k);
    build(1, n, 1); for (int i = 1; i <= m; i++) f[i] = inf;
    for (int i = 1; i <= k; i++) {
        scanf("%d%d%d%d", s + i, t + i, d + i, w + i);
        update(s[i], t[i], {w[i], d[i]}, 1, n, 1);
    }
    for (int i = 1; i <= n; i++) {
        PII tot = query(i, 1, n, 1);
        if (tot.first == 0 && tot.second == 0) continue;
        int k = 0;
        for (int j = 1; j <= m; j++) {
            if (i + j + k > n) tt[j] = make_pair(0, 1e9);
            else {
                PII x = query(i + j + k, 1, n, 1);
                tt[j] = x;
                if (x.first == 0 && x.second == 0) {
                    j--; k++;
                }
            }
        }
        // dbg(i, tot.first, tot.second);
        for (int j = m - 1; j >= 0; j--) {
            if (i <= g[j]) continue;
            dbg(i, j);
            for (int k = 1; j + k <= m; k++) {
                if (f[j] + tt[k].first < f[j + k] || (f[j] + tt[k].first == f[j + k] && tt[k].second > g[j + k])) {
                    f[j + k] = f[j] + tt[k].first;
                    g[j + k] = tt[k].second;
                    dbg(i, j, k, f[j + k]);
                }
            }
            // if (f[j] + tot2.first < f[j + 1] || (f[j] + tot2.first == f[j + 1] && tot2.second > g[j + 1])) {
            //     f[j + 1] = f[j] + tot2.first;
            //     g[j + 1] = tot2.second;
            //     dbg(i, j, f[j + 1], g[j + 1]);
            // }
        }
        if (i > g[0]) {
            f[0] += tot.first;
            g[0] = tot.second;
        }
        for (int j = 1; j <= m; j++) {
            if (i <= g[j]) continue;
            if (f[j] >= inf) continue;
            f[j] += tot.first;
            g[j] = tot.second;
        }
        dbg(i);
        for (int i = 0; i <= m; i++) dbg(i, f[i], g[i]);
    }
    ll ans = 1e18;
    for (int i = 0; i <= m; i++) ans = min(ans, f[i]);
    cout << ans << endl;
    return 0;
}