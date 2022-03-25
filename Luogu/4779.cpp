#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 3000000 + 5;

// Pairing Heap
template <typename T> 
struct Heap {
    T val[maxn];
    int tot, rt, sz, ch[maxn], xd[maxn];
    void clear() {
        tot = rt = sz = 0;
    }
    Heap() {
        clear();
    }
    int node(T x) {
        val[++tot] = x; 
        ch[tot] = xd[tot] = 0;
        return tot;
    }
    int merge(int a, int b) {
        if (!a || !b) return a + b;
        if (val[a] < val[b]) swap(a, b);
        xd[b] = ch[a]; ch[a] = b;
        return a;
    }
    int merges(int x) {
        if (!x || !xd[x]) return x;
        int a = xd[x], b = xd[a];
        xd[x] = xd[a] = 0;
        return merge(merge(x, a), merges(b));
    }
    void push(T x) {
        sz++;
        if (rt == 0) rt = node(x);
        else rt = merge(rt, node(x));
    }
    T top() {
        return val[rt];
    }
    T pop() {
        sz--;
        T tp = val[rt];
        rt = merges(ch[rt]);
        return tp;
    }
};

struct edge {
    int to, nxt, d;
} g[maxn];
int tot, head[maxn];
void adde(int u, int v, int d) {
    g[++tot] = {v, head[u], d}; head[u] = tot;
}

struct node {
    int to; ll dis;
    bool operator < (const node& b) const {
        return dis > b.dis;
    }
};

Heap<node> pq;

int n, m, s;
int vis[maxn];
ll dis[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, d; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &d);
        adde(u, v, d);
    }
    for (int i = 1; i <= n; i++) dis[i] = 1ll << 60;
    pq.push({1, 0}); dis[1] = 0;
    while (pq.sz) {
        node tp = pq.top(); pq.pop();
        if (vis[tp.to]) continue;
        vis[tp.to] = 1;
        for (int i = head[tp.to]; i; i = g[i].nxt) {
            int v = g[i].to, d = g[i].d;
            if (vis[v]) continue;
            if (dis[v] > dis[tp.to] + d) {
                dis[v] = dis[tp.to] + d;
                pq.push({v, dis[v]});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i > 1) putchar(' ');
        printf("%d", dis[i]);
    }
    return 0;
}