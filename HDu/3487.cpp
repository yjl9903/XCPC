#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;
const int inf = 1 << 30;

int n, m, a[maxn];
vector<int> v;

struct Splay{
    int f[maxn], ch[maxn][2], size[maxn], rev[maxn], key[maxn], root, sz;
    void clear(){
        root = sz = f[0] = ch[0][0] = ch[0][1] = size[0] = 0;
    }
    int get(int x){return ch[f[x]][1] == x;}
    void pushup(int rt){ size[rt] = 1 + size[ch[rt][0]] + size[ch[rt][1]]; }
    void pushdown(int rt){
        if (!rev[rt]) return;
        rev[rt] = 0; rev[ch[rt][0]] ^= 1; rev[ch[rt][1]] ^= 1;
        swap(ch[rt][0], ch[rt][1]);
    }
    int build(int l, int r, int rt){
        if (l > r) return 0;
        int m = (l + r) >> 1, tot = ++sz;
        f[tot] = rt; key[tot] = a[m]; rev[tot] = 0;
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
    int findmax(){
        int tot = root;
        pushdown(tot);
        while (ch[tot][1]){
            tot = ch[tot][1];
            pushdown(tot);
        }
        return tot;
    }
    void reverse(int l, int r){
        int x = find(l), y = find(r + 2);
        splay(x, 0); splay(y, x);
        rev[ch[y][0]] ^= 1;
    }
    void split(int l, int r, int k){
        int x = find(l), y = find(r + 2);
        splay(x, 0); splay(y, x);
        int r1 = ch[y][0]; ch[y][0] = 0;
        pushup(y); pushup(x);
        splay(find(k + 1), 0);
        int r2 = ch[root][1];
        ch[root][1] = r1; f[r1] = root;
        pushup(root);
        splay(findmax(), 0);
        ch[root][1] = r2; f[r2] = root;
        pushup(root);
    }
    void print(int p){
        pushdown(p);
        if (ch[p][0]) print(ch[p][0]);
        if (key[p] != inf) v.push_back(key[p]);
        if (ch[p][1]) print(ch[p][1]);
    }
}f;

int main(){
    while (~scanf("%d%d", &n, &m)){
        if (n <= -1 && m <= -1) break;
        for (int i = 1; i <= n; i++) a[i + 1] = i;
        a[1] = a[n + 2] = inf;
        f.clear();
        f.root = f.build(1, n + 2, 0);
        char cmd[10]; int l, r, k;
        while (m--){
            scanf("%s", cmd);
            if (cmd[0] == 'C'){
                scanf("%d%d%d", &l, &r, &k);
                f.split(l, r, k);
            }
            else if (cmd[0] == 'F'){
                scanf("%d%d", &l, &r);
                f.reverse(l, r);
            }
        }
        v.clear();
        f.print(f.root);
        for (int i = 0; i < v.size(); i++) printf("%d%c", v[i], " \n"[i + 1 == v.size()]);
    }
    return 0;
}