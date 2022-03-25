#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const ll inf = 1ll << 60;

int n, m;

namespace kdt{
    int rt, cmpd;
    struct node{
        int d[3], mx[3], mn[3], l, r, id;
        bool operator<(const node& b)const{
            return d[kdt::cmpd] < b.d[kdt::cmpd];
        }
    }tree[maxn];

    inline void pushup(int u, int v){
        node& a = tree[u], & b = tree[v];
        for (int i = 0; i < 3; i++){
            a.mx[i] = max(a.mx[i], b.mx[i]);
            a.mn[i] = min(a.mn[i], b.mn[i]);
        }
    }
    inline int build(int l, int r, int k){
        int m = l + r >> 1; cmpd = k;
        nth_element(tree + l, tree + m, tree + r + 1);
        node& t = tree[m]; t.l = t.r = 0;
        for (int i = 0; i < 3; i++) t.mx[i] = t.mn[i] = t.d[i];
        if (l != m){
            t.l = build(l, m - 1, (k + 1) % 3);
            pushup(m, t.l);
        }
        if (r != m){
            t.r = build(m + 1, r, (k + 1) % 3);
            pushup(m, t.r);
        }
        return m;
    }

    ll d, x, y; int ans, c;
    inline ll sqr(ll x){return x * x;}
    inline ll distance(const node& a, ll x, ll y){
        x -= a.d[0]; y -= a.d[1]; return x * x + y * y;
    }
    inline ll cal(int p, ll x, ll y){
        ll ans = 0; node& a = tree[p];
        if (a.mn[2] > c) return inf;
        if (x < a.mn[0]) ans += sqr(a.mn[0] - x);
        if (x > a.mx[0]) ans += sqr(a.mx[0] - x);
        if (y < a.mn[1]) ans += sqr(a.mn[1] - y);
        if (y > a.mx[1]) ans += sqr(a.mx[1] - y);
        return ans;
    }

    inline void query(int p){
        node& t = tree[p];
        ll d0 = distance(t, x, y), dl = inf, dr = inf;
        if (t.d[2] > c) d0 = inf;
        if (d0 < d || (d0 == d && t.id < tree[ans].id)){
            d = d0; ans = p;
        }
        if (t.l) dl = cal(t.l, x, y);
        if (t.r) dr = cal(t.r, x, y);
        if (dl < dr){
            if (dl <= d) query(t.l);
            if (dr <= d) query(t.r);
        }
        else {
            if (dr <= d) query(t.r);
            if (dl <= d) query(t.l);
        }
    }
}
using namespace kdt;

int query(int a, int b, int tc){
    ans = 0; d = inf;
    x = a; y = b; c = tc;
    query(rt); return ans;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++){
            for (int j = 0; j < 3; j++) scanf("%d", &tree[i].d[j]);
            tree[i].id = i;
        }
        rt = build(1, n, 0); int x, y, c;
        while (m--){
            scanf("%d%d%d", &x, &y, &c);
            int r = query(x, y, c);
            printf("%d %d %d\n", tree[ans].d[0], tree[ans].d[1], tree[ans].d[2]);
        }
    }
    return 0;
}