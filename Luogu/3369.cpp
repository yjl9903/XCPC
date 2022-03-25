#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int rand(){
    static int seed = 233;
    return seed = int(seed * 482711ll % 2147483647);
}

struct fhqTreap{
    int ch[maxn][2], key[maxn], rnd[maxn], size[maxn], root, tot;
    fhqTreap(){ root = tot = 0; }
    int node(int v){
        key[++tot] = v; rnd[tot] = rand();
        size[tot] = 1;
        ch[tot][0] = ch[tot][1] = 0;
        return tot;
    }
    void pushup(int x){ size[x] = size[ch[x][0]] + size[ch[x][1]] + 1; }
    void split(int now, int k, int &x, int &y){
        if (!now){
            x = y = 0; return;
        }
        if (key[now] <= k){
            x = now;
            split(ch[now][1], k, ch[now][1], y);
        }
        else {
            y = now;
            split(ch[now][0], k, x, ch[now][0]);
        }
        pushup(now);
    }
    int merge(int x, int y){
        if (x == 0 || y == 0) return x + y;
        if (rnd[x] < rnd[y]){
            ch[x][1] = merge(ch[x][1], y);
            pushup(x); return x;
        }
        else {
            ch[y][0] = merge(x, ch[y][0]);
            pushup(y); return y;
        }
    }
    void insert(int v){
        int x = 0, y = 0;
        split(root, v, x, y);
        root = merge(merge(x, node(v)), y);
    }
    void del(int v){
        int x = 0, y = 0, z = 0;
        split(root, v, x, z);
        split(x, v - 1, x, y);
        y = merge(ch[y][0], ch[y][1]);
        root = merge(merge(x, y), z);
    }
    int find(int v){
        int x = 0, y = 0;
        split(root, v - 1, x, y);
        int ans = size[x] + 1;
        root = merge(x, y);
        return ans;
    }
    int findx(int now, int rank){
        while (1){
            if (size[ch[now][0]] >= rank) now = ch[now][0];
            else if (size[ch[now][0]] + 1 == rank) return key[now];
            else {
                rank -= size[ch[now][0]] + 1;
                now = ch[now][1];
            }
        }
    }
    int prev(int v){
        int x = 0, y = 0; 
        split(root, v - 1, x, y);
        int ans = findx(x, size[x]);
        root = merge(x, y);
        return ans;
    }
    int succ(int v){
        int x = 0, y = 0;
        split(root, v, x, y);
        int ans = findx(y, 1);
        root = merge(x, y);
        return ans;
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
            case 4: printf("%d\n", f.findx(f.root, x)); break;
            case 5: printf("%d\n", f.prev(x)); break;
            case 6: printf("%d\n", f.succ(x)); break;
        }
    }
    return 0;
}