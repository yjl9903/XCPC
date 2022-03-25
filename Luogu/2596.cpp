#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace Treap {
    mt19937 rand(23333);
    int ch[maxn][2], val[maxn], rnd[maxn], siz[maxn], tot, rt;
    void clear() {
        rt = tot = 0;
    }
    void pushup(int rt) { 
        siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + 1;
    }
    int node(int v) {
        val[++tot] = v; rnd[tot] = rand(); 
        siz[tot] = 1;
        ch[tot][0] = ch[tot][1] = 0;
        return pos[v] = tot;
    }
    void split(int now, int k, int& x, int& y) {
        if (!now) {
            x = y = 0; return ;
        }
        if (siz[now] <= k) {
            x = now; split(ch[now][1], k, ch[now][1], y);
        } else {
            y = now; split(ch[now][0], k, x, ch[now][0]);
        }
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (rnd[x] < rnd[y]) {
            ch[x][1] = merge(ch[x][1], y);
            pushup(x); return x;
        } else {
            ch[y][0] = merge(x, ch[y][0]);
            pushup(y); return y;
        }
    }
    void insert(int p, int v) {
        int x = 0, y = 0;
        split(rt, p, x, y);
        rt = merge(merge(x, node(v)), y);
    }
}
using namespace Treap;

int n, m, a[maxn], pos[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        insert(a[i]);
    }
    char op[10]; int s, t;
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'T') {
            scanf("%d", &s);

        }
        if (op[0] == 'B') {
            scanf("%d", &s);

        }
        if (op[0] == 'I') {

        }
        if (op[0] == 'A') {

        }
        if (op[0] == 'Q') {

        }
    }
    return 0;
}