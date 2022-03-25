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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct lct {
    int fa[maxn], ch[maxn][2], rev[maxn], s[maxn], si[maxn];
    int nroot(int x) { return ch[fa[x]][0] == x || ch[fa[x]][1] == x; }
    int get(int x) { return ch[fa[x]][1] == x; }
    void pushup(int x) { 
        s[x] = s[ch[x][0]] + s[ch[x][1]] + si[x] + 1;
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
    void access(int x) {
        for (int y = 0; x; y = x, x = fa[x]) {
            splay(x);
            si[x] += s[ch[x][1]] - s[y];
            ch[x][1] = y;
            pushup(x);
        }
    }
    void make(int x) {
        access(x); splay(x); pushrev(x);
    }
    int findroot(int x) {
        access(x); splay(x);
        while (ch[x][0]) pushdown(x), x = ch[x][0];
        return x;
    }
    int link(int x, int y) {
        make(x); make(y);
        fa[x] = y; si[y] += s[x];
        pushup(y);
        return 1;
    }
    void split(int x, int y) {
        make(x); access(y); splay(y);
    }
} f;

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    char op[2]; int x, y;
    while (m--) {
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'A') {
            f.link(x, y);
        } else {
            // f.make(x); f.make(y);
            f.split(x, y);
            dbg(x, y, f.fa[x], f.fa[y]);
            printf("%lld\n", 1ll * f.s[x] * (f.s[y] - f.s[x]));
        }
    }
    return 0;
}