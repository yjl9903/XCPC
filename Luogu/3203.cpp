#include <cstdio>
using namespace std;
const int maxn = 200000 + 5;

int n, m, a[maxn];

struct lct{
    int ch[maxn][2], fa[maxn], size[maxn];
    int nroot(int x){return ch[fa[x]][0] == x || ch[fa[x]][1] == x;}
    int get(int x){return ch[fa[x]][1] == x;}
    void pushup(int x){
        size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    }
    void rot(int x){
        int old = fa[x], oldf = fa[old], k = get(x), w = ch[x][k ^ 1];
        if (nroot(old)) ch[oldf][ch[oldf][1] == old] = x;
        ch[x][k ^ 1] = old; ch[old][k] = w;
        if (w) fa[w] = old;
        fa[old] = x; fa[x] = oldf;
        pushup(old); pushup(x);
    }
    void splay(int x){
        int y = x;
        while (nroot(x)){
            y = fa[x];
            if (nroot(y)) rot(get(x) == get(y) ? y : x);
            rot(x);
        }
        pushup(x);
    }
    void access(int x){
        for (int y = 0; x; y = x, x = fa[x])
            splay(x), ch[x][1] = y, pushup(x);
    }
}f;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        f.size[i] = 1;
        if (i + a[i] <= n) f.fa[i] = i + a[i];
    }
    scanf("%d", &m); int cmd, x, y;
    while (m--){
        scanf("%d", &cmd);
        if (cmd == 1){
            scanf("%d", &x); x++;
            f.access(x); f.splay(x);
            printf("%d\n", f.size[x]);
        }
        if (cmd == 2){
            scanf("%d%d", &x, &y); x++;
            f.access(x); f.splay(x);
            f.ch[x][0] = f.fa[f.ch[x][0]] = 0;
            if (x + y <= n) f.fa[x] = x + y;
            f.pushup(x);
        }
    }
    return 0;
}