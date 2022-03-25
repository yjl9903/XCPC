#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int inf = 1 << 30;

inline int rand(){
    static int seed = 233;
    return seed = int(seed * 48271LL % 2147483647);
}

struct Treap{
    int ch[maxn][2], key[maxn], size[maxn], rnd[maxn], cnt[maxn], sz, root;
    Treap(){ 
        root = sz = 0;
    }
    void pushup(int rt){ size[rt] = size[ch[rt][0]] + size[ch[rt][1]] + cnt[rt]; }
    void rot(int& x, int k){
        int v = ch[x][k ^ 1];
        ch[x][k ^ 1] = ch[v][k];
        ch[v][k] = x;
        x = v;
        pushup(ch[x][k]); pushup(x);
    }
    void insert(int& x, int val){
        if (!x){
            x = ++sz;
            ch[x][0] = ch[x][1] = 0;
            key[x] = val; rnd[x] = rand();
            size[x] = cnt[x] = 1;
            return;
        }
        if (key[x] == val){
            cnt[x]++; pushup(x); 
            return;
        }
        int k = val > key[x];
        insert(ch[x][k], val);
        if (rnd[x] < rnd[ch[x][k]]) rot(x, k ^ 1);
        pushup(x);
    }
    void del(int& x, int val){
        if (!x) return;
        if (key[x] == val){
            if (cnt[x] > 1) {
                cnt[x]--; pushup(x); 
                return;
            }
            if (ch[x][0] || ch[x][1]){
                if (!ch[x][1] || rnd[ch[x][0]] > rnd[ch[x][1]]){
                    rot(x, 1); del(ch[x][1], val);
                }
                else {
                    rot(x, 0); del(ch[x][0], val);
                }
                pushup(x);
                return;
            }
            x = 0;
            return;
        }
        del(ch[x][val > key[x]], val);
        pushup(x);
    }
    int find(int x, int val){
        if (!x) return 0;
        if (val == key[x]) return size[ch[x][0]] + 1;
        else if (val < key[x]) return find(ch[x][0], val);
        else return size[ch[x][0]] + cnt[x] + find(ch[x][1], val);
    }
    int findx(int x, int rank){
        if (!x) return inf;
        if (rank <= size[ch[x][0]]) return findx(ch[x][0], rank);
        else if (rank <= size[ch[x][0]] + cnt[x]) return key[x];
        else return findx(ch[x][1], rank - size[ch[x][0]] - cnt[x]);
    }
    int prev(int v){
        int x = root, ans = 0;
        while (x){
            if (v > key[x]) ans = key[x], x = ch[x][1];
            else x = ch[x][0];
        }
        return ans;
    }
    int succ(int v){
        int x = root, ans = 0;
        while (x){
            if (v < key[x]) ans = key[x], x = ch[x][0];
            else x = ch[x][1];
        }
        return ans;
    }
}f;

int n;

int main(){
    scanf("%d", &n);
    int cmd, x;
    while (n--){
        scanf("%d%d", &cmd, &x);
        int& root = f.root;
        switch(cmd){
            case 1: f.insert(root, x); break;
            case 2: f.del(root, x); break;
            case 3: printf("%d\n", f.find(root, x)); break;
            case 4: printf("%d\n", f.findx(root, x)); break;
            case 5: printf("%d\n", f.prev(x)); break;
            case 6: printf("%d\n", f.succ(x)); break;
        }
    }
    return 0;
}