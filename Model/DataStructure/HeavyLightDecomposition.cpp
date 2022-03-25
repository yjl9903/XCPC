#include <cstdio>
#include <algorithm>
const int maxn = 100000 + 5;
const int inf = 1 << 30;

int a[maxn];
struct Splay{
    int f[maxn], ch[maxn][2], size[maxn], rev[maxn] = {0}, key[maxn], root, sz;
    Splay(){
        root = sz = size[0] = rev[0] = f[0] = 0; key[0] = inf;
    }
    int get(int x){return ch[f[x]][1] == x;}
    void pushup(int x){
        size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    }
    void pushdown(int x){
        if (!rev[x]) return;
        std::swap(ch[x][0], ch[x][1]);
        rev[ch[x][0]] ^= 1; rev[ch[x][1]] ^= 1; rev[x] = 0;
    }
    int build(int l, int r, int rt){
        if (l > r) return 0;
        int m = (l + r) >> 1, tot = ++sz;
        key[tot] = a[m]; f[tot] = rt; rev[tot] = 0;
        ch[tot][0] = build(l, m - 1, tot);
        ch[tot][1] = build(m + 1, r, tot);
        pushup(tot);
        return tot;
    }
    void rot(int x){
        int old = f[x], oldf = f[old], tp = get(x);
        pushdown(old); pushdown(x);
        ch[old][tp] = ch[x][tp ^ 1]; f[ch[old][tp]] = old;
        ch[x][tp ^ 1] = old; f[old] = x; 
        f[x] = oldf;
        if (oldf) ch[oldf][ch[oldf][1] == old] = x;
        pushup(old); pushup(x);
    }
    void splay(int x, int tar){
        for (int fa; (fa = f[x]) != tar; rot(x))
            if (f[fa] != tar)
                rot(get(fa) == get(x) ? fa : x);
        if (!tar) root = x;
    }
    int find(int k){
        int tot = root;
        while (1){
            pushdown(tot);
            if (k <= size[ch[tot][0]]) tot = ch[tot][0];
            else {
                k -= size[ch[tot][0]] + 1;
                if (!k) return tot;
                tot = ch[tot][1];
            }
        }
    }
    void reverse(int l, int r){
        int a = find(l), b = find(r + 2);
        splay(a, 0); splay(b, a);
        rev[ch[b][0]] ^= 1;
    }
    void print(int p){
        pushdown(p);
        if (ch[p][0]) print(ch[p][0]);
        if (key[p] != inf) printf("%d ", key[p]);
        if (ch[p][1]) print(ch[p][1]);
    }
}f;

int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) a[i + 1] = i;
    a[1] = inf; a[n + 2] = inf;
    f.root = f.build(1, n + 2, 0);
    while (m--){
        int l, r; scanf("%d%d", &l, &r);
        f.reverse(l, r);
    }
    f.print(f.root);
    return 0;
}