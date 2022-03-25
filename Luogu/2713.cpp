#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

namespace pairHeap {
    struct node {
        int val, id, head, nxt, fa;
        node() { head = nxt = fa = 0; }
    } a[maxn];
    int rt[maxn];
    inline int merge(int u, int v) {
        if (!u || !v) return u + v;
        if (a[u].val > a[v].val) swap(u, v);
        a[v].nxt = a[u].head; a[u].head = v; a[v].fa = u;
        return u;
    }
    inline int pop(int x) {
        queue<int> q;
        int tp = 0;
        for (int i = a[x].head; i; i = a[i].nxt) {
            q.push(i); a[i].fa = 0;
        }
        while (q.size() > 1) {
            int x = q.front(); q.pop(); 
            int y = q.front(); q.pop();
            q.push(merge(x, y));
        }
        if (q.size()) return q.front();
        else return 0;
    }
}
using namespace pairHeap;

int n, q, vis[maxn], pre[maxn];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i].val), a[i].id = i, pre[i] = rt[i] = i;
    scanf("%d", &q); char op[2]; int x, y;
    while (q--) {
        scanf("%s%d", op, &x);
        if (op[0] == 'M') {
            scanf("%d", &y);
            if (vis[x] || vis[y]) continue;
            x = find(x); y = find(y);
            if (x == y) continue;
            pre[y] = x;
            rt[x] = merge(rt[x], rt[y]);
        }
        if (op[0] == 'K') {
            if (vis[x]) {
                puts("0"); continue;
            }
            x = find(x);
            printf("%d\n", a[rt[x]].val);
            vis[a[rt[x]].id] = 1;
            rt[x] = pop(rt[x]);
        }
    }
    return 0;
}