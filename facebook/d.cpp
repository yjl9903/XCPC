#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200 + 5;

struct lct {
    int fa[maxn], ch[maxn][2], rev[maxn];
    void clear() {
        ms(fa, 0); ms(ch, 0); ms(rev, 0);
    }
    int nroot(int x) { return ch[fa[x]][0] == x || ch[fa[x]][1] == x; }
    int get(int x) { return ch[fa[x]][1] == x; }
    void pushup(int x) { 

    }
    void pushrev(int x) {
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void pushdown(int x) {
        if (!rev[x]) return;
        if (ch[x][0]) pushrev(ch[x][0]);
        if (ch[x][1]) pushrev(ch[x][1]);
        rev[x] = 0;
    }
    void rot(int x) {
        int old = fa[x], oldf = fa[old], k = get(x), w = ch[x][k ^ 1];
        if (nroot(old)) ch[oldf][ch[oldf][1] == old] = x; 
        ch[x][k ^ 1] = old; ch[old][k] = w;
        if (w) fa[w] = old; 
        fa[old] = x; fa[x] = oldf;
        pushup(old);
    }
    int st[maxn];
    void splay(int x) {
        int y = x, t = 0;
        st[++t] = y;
        while (nroot(y)) st[++t] = fa[y], y = fa[y];
        while (t) pushdown(st[t--]);
        while (nroot(x)) {
            y = fa[x];
            if (nroot(y)) rot(get(x) == get(y) ? y : x);
            rot(x); 
        }
        pushup(x);
    }
    int access(int x){
        int r = 0;
        for (int y = 0; x; y = x, x = fa[x])
            splay(r = x), ch[x][1] = y, pushup(x);
        return r;
    }
    int qlca(int u, int v) {
        access(u); return access(v);
    }
    void make(int x) {
        access(x); splay(x); pushrev(x);
    }
    int findroot(int x) {
        access(x); splay(x); // findroot 把待检查的元素转上去了
        while (ch[x][0]) pushdown(x), x = ch[x][0];
        // splay(x); // ?
        return x;
    }
    void split(int x, int y) {
        make(x); access(y); splay(y);
    }
    int link(int x, int y) {
        make(x);
        if (findroot(y) == x) return 0;
        fa[x] = y;
        return 1;
    }
    int cut(int x, int y) {
        // split(x, y); fa[x] = ch[y][0] = 0; pushup(y);
        make(x);
        if (findroot(y) != x || fa[x] != y || ch[x][1]) return 0;
        // if (findroot(y) != x || size[y] > 2) return 0;
        fa[x] = ch[y][0] = 0;
        pushup(y);
        return 1;
    }
    int same(int u, int v) {
        return findroot(u) == findroot(v);
    }
} f;

mt19937 rnd(time(0));

int n, m, x[maxn], y[maxn], z[maxn], p[maxn], ans[maxn];

int solve() {
    f.clear();
    for (int i = 1; i <= m; i++) {
        int tx = x[p[i]], ty = y[p[i]], tz = z[p[i]];
        if (!f.same(tx, tz)) f.link(f.findroot(tx), tz);
        if (!f.same(ty, tz)) f.link(f.findroot(ty), tz);
    }
    int r;
    for (int i = 1; i <= m; i++) {
        int tx = x[p[i]], ty = y[p[i]], tz = z[p[i]];
        r = tx;
        if (f.qlca(tx, ty) != tz) return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (f.fa[i]) ans[i] = f.fa[i];
    }
    return 1;
}

const int T = 1000000000;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        ms(ans, 0);
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++) scanf("%d%d%d", x + i, y + i, z + i), p[i] = i;
        int flag = 0;
        for (int t = 0; t < T; t++) {
            shuffle(p + 1, p + 1 + m, rnd);
            if (solve()) {
                flag = 1;
                break;
            }
        }
        printf("Case #%d:", ++kase);
        if (flag)
            for (int i = 1; i <= n; i++) printf(" %d", ans[i]);
        else 
            printf(" Impossible");
        puts("");
    }
    return 0;
}