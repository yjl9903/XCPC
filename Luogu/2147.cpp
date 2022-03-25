#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m;

struct Lct{
    int ch[maxn][2], fa[maxn], rev[maxn];
    bool nroot(int x){return ch[fa[x]][0] == x || ch[fa[x]][1] == x;}
    bool get(int x){return ch[fa[x]][1] == x;}
    void pushup(int x){}
    void pushrev(int x){swap(ch[x][0], ch[x][1]); rev[x] ^= 1;}
    void pushdown(int x){
        if (!rev[x]) return;
        if (ch[x][0]) pushrev(ch[x][0]);
        if (ch[x][1]) pushrev(ch[x][1]);
        rev[x] = 0;
    }
    void rot(int x){
        int old = fa[x], oldf = fa[old], k = get(x), w = ch[x][k ^ 1];
        if (nroot(old)) ch[oldf][ch[oldf][1] == old] = x;
        ch[x][k ^ 1] = old; ch[old][k] = w;
        if (w) fa[w] = old;
        fa[old] = x; fa[x] = oldf;
        // pushup(old);
    }
    int st[maxn];
    void splay(int x){
        int y = x, t = 0;
        st[++t] = y;
        while (nroot(y)) st[++t] = fa[y], y = fa[y];
        while (t) pushdown(st[t--]);
        while (nroot(x)){
            y = fa[x];
            if (nroot(y)) rot(get(x) == get(y) ? y : x);
            rot(x);
        }
        // pushup(x);
    }
    void access(int x){
        for (int y = 0; x; y = x, x = fa[x])
            splay(x), ch[x][1] = y; // pushup(x);
    }
    void make(int x){
        access(x); splay(x); pushrev(x);
    }
    int findroot(int x){
        access(x); splay(x);
        while (ch[x][0]) pushdown(x), x = ch[x][0];
        splay(x);
        return x;
    }
    void split(int x, int y){
        make(x); access(y); splay(y);
    }
    void link(int x, int y){
        make(x); fa[x] = y;
    }
    void cut(int x, int y){
        split(x, y);
        fa[x] = ch[y][0] = 0;
        // pushup(y);
    }
}f;

int main(){
    scanf("%d%d", &n, &m);
    char cmd[20]; int u, v;
    while (m--){
        scanf("%s%d%d", cmd, &u, &v);
        if (cmd[0] == 'Q'){
            f.make(u); 
            if (f.findroot(v) == u) puts("Yes");
            else puts("No");
        }
        else if (cmd[0] == 'D'){
            f.cut(u, v);
        }
        else if (cmd[0] == 'C'){
            f.link(u, v);
        }
    }
    return 0;
}