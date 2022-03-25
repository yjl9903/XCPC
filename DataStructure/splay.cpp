#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1000000 + 5;

struct Splay{
    int f[maxn], ch[maxn][2], key[maxn], cnt[maxn], size[maxn], sz = 0, root = 0;
    Splay(){sz = root = 0;}
    void clean(int x){
        ch[x][0] = ch[x][1] = f[x] = key[x] = cnt[x] = size[x] = 0;
    }
    int get(int x){
        return ch[f[x]][1] == x;
    }
    void update(int x){
        if (!x) return;
        size[x] = cnt[x];
        if (ch[x][0]) size[x] += size[ch[x][0]];
        if (ch[x][1]) size[x] += size[ch[x][1]];
    }
    void rot(int x){
        int old = f[x], oldf = f[old], tp = get(x);
        ch[old][tp] = ch[x][tp ^ 1]; f[ch[old][tp]] = old;
        f[old] = x; ch[x][tp ^ 1] = old;
        f[x] = oldf;
        if (oldf) ch[oldf][ch[oldf][1] == old] = x;
        update(old); update(x);
    }
    void splay(int x){
        for (int fa; fa = f[x]; rot(x))
            if (f[fa]) rot(get(x) == get(fa) ? fa : x);
        root = x;
    }
    int insert(int v){
        if (root == 0){
            sz++; ch[sz][0] = ch[sz][1] = f[sz] = 0;
            key[sz] = v; cnt[sz] = 1; size[sz] = 1; 
            root = sz;
            return 1;
        }
        int tot = root, fa = 0;
        while (1){
            if (key[tot] == v){
                cnt[tot]++; update(tot); update(fa);
                splay(tot);
                return cnt[tot];
            }
            fa = tot;
            tot = ch[tot][v > key[tot]];
            if (tot == 0){
                sz++; ch[sz][0] = ch[sz][1] = 0; 
                key[sz] = v; cnt[sz] = size[sz] = 1;
                f[sz] = fa; ch[fa][v > key[fa]] = sz;
                update(fa); splay(sz);
                break;
            }
        }
        return 1;
    }
    int find(int v){
        int ans = 0, tot = root;
        while (1){
            if (v < key[tot]) tot = ch[tot][0];
            else {
                ans += (ch[tot][0] ? size[ch[tot][0]] : 0);
                if (v == key[tot]){
                    splay(tot); return ans + 1;
                }
                ans += cnt[tot];
                tot = ch[tot][1];
            } 
        }
        return 0;
    }
    int findx(int x){
        int tot = root;
        while (1){
            if (ch[tot][0] && x <= size[ch[tot][0]]) tot = ch[tot][0];
            else {
                int t = (ch[tot][0] ? size[ch[tot][0]] : 0) + cnt[tot];
                if (x <= t) return key[tot];
                x -= t; tot = ch[tot][1];
            }
        }
        return -1;
    }
    int prev(){
        int tot = ch[root][0];
        while (ch[tot][1]) tot = ch[tot][1];
        return tot;
    }
    int succ(){
        int tot = ch[root][1];
        while (ch[tot][0]) tot = ch[tot][0];
        return tot;
    }
    void del(int v){
        find(v);
        if (cnt[root] > 1){
            cnt[root]--; return;
        }
        if (!ch[root][0] && !ch[root][1]){
            clean(root); root = 0; return;
        }
        if (!ch[root][0]){
            int old = root; root = ch[root][1]; f[root] = 0;
            clean(old); return;
        }
        else if (!ch[root][1]){
            int old = root; root = ch[root][0]; f[root] = 0;
            clean(old); return;
        }
        int lf = prev(), old = root;
        splay(lf); f[ch[old][1]] = root; ch[root][1] = ch[old][1];
        clean(old); update(root);
    }
}f;
int n;

int main(){
    scanf("%d", &n);
    int cmd, x;
    while (n--){
        scanf("%d%d", &cmd, &x);
        switch(cmd){
            case 1: f.insert(x); break;
            case 2: f.del(x); break;
            case 3: printf("%d\n", f.find(x)); break;
            case 4: printf("%d\n", f.findx(x)); break;
            case 5: f.insert(x); printf("%d\n", f.key[f.prev()]); f.del(x); break;
            case 6: f.insert(x); printf("%d\n", f.key[f.succ()]); f.del(x); break;
        }
    }
    return 0;
}