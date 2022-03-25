#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 600000 + 5;
const int inf = 1 << 30;

namespace kdt{
    int rt, cmpd;
    struct node{
        int d[2], mx[2], mn[2], l, r, id;
        bool operator<(const node& b)const{
            return d[kdt::cmpd] < b.d[kdt::cmpd];
        }
    }tree[maxn];

    inline void pushup(int u, int v){
        node& a = tree[u], & b = tree[v];
        for (int i = 0; i < 2; i++){
            a.mx[i] = max(a.mx[i], b.mx[i]);
            a.mn[i] = min(a.mn[i], b.mn[i]);
        }
    }
    inline int build(int l, int r, int k){
        int m = l + r >> 1; cmpd = k;
        nth_element(tree + l, tree + m, tree + r + 1);
        node& t = tree[m]; t.l = t.r = 0;
        for (int i = 0; i < 2; i++) t.mx[i] = t.mn[i] = t.d[i];
        if (l != m){
            t.l = build(l, m - 1, k ^ 1);
            pushup(m, t.l);
        }
        if (r != m){
            t.r = build(m + 1, r, k ^ 1);
            pushup(m, t.r);
        }
        return m;
    }

    inline int distance(const node& a, int x, int y){
        x -= a.d[0]; y -= a.d[1]; return abs(x) + abs(y);
    }
    inline int cal(int p, int x, int y){ // cut
        int ans = 0; node& a = tree[p];
        if (x < a.mn[0]) ans += a.mn[0] - x;
        if (x > a.mx[0]) ans += x - a.mx[0];
        if (y < a.mn[1]) ans += a.mn[1] - y;
        if (y > a.mx[1]) ans += y - a.mx[1];
        return ans;
    }
		
  	int ans, x, y;
    inline void query(int p){
        node& t = tree[p];
        int d0 = distance(t, x, y), dl = inf, dr = inf;
        // if (x == t.d[0] && y == t.d[1]) d0 = inf; //cut
        ans = min(ans, d0);
        if (t.l) dl = cal(t.l, x, y);
        if (t.r) dr = cal(t.r, x, y);
        if (dl < dr){
            if (dl < ans) query(t.l);
            if (dr < ans) query(t.r);
        }
        else {
            if (dr < ans) query(t.r);
            if (dl < ans) query(t.l);
        }
    }
    inline int query(int a, int b){
        x = a; y = b; ans = inf;
        query(rt); return ans;
    }
    inline int insert(int x, int y, int p){
        node& t = tree[p]; t.l = t.r = 0;
        t.mx[0] = t.mn[0] = t.d[0] = x;
        t.mx[1] = t.mn[1] = t.d[1] = y;
        int now = rt, k = 0;
        while (true){
            pushup(now, p);
            if (tree[now].d[k] <= tree[p].d[k]){
                if (!tree[now].l) return tree[now].l = p;
                now = tree[now].l;
            }
            else {
                if (!tree[now].r) return tree[now].r = p;
                now = tree[now].r;
            }
            k ^= 1;
        }
        return 0;
    }
}
using namespace kdt;

int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++){
        scanf("%d%d", &tree[i].d[0], &tree[i].d[1]);
    }
    rt = build(1, n, 0); int op, x, y;
    while (m--){
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1){
            insert(x, y, ++n);
        }
        if (op == 2){
            printf("%d\n", query(x, y));
        }
    }
    return 0;
}