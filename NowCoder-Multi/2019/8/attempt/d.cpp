#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

namespace kdt{
    int rt, cmpd;
    struct node{
        int d[3], mx[3], mn[3], l, r, id;
        bool operator<(const node& b)const{
            return d[kdt::cmpd] < b.d[kdt::cmpd];
        }
    } tree[maxn];

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
        for (int i = 0; i < 3; i++) 
            t.mx[i] = t.mn[i] = t.d[i];
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

    inline int distance(const node& a, int x, int y, int z) {
        x -= a.d[0]; y -= a.d[1]; z -= a.d[2];
        return abs(x) + abs(y) + abs(z);
    }
    inline int cal(int p, int x, int y, int z) { // cut
        ll ans = 0; node& a = tree[p];
        if (x < a.mn[0]) ans += abs(a.mn[0] - x);
        if (x > a.mx[0]) ans += abs(a.mx[0] - x);
        if (y < a.mn[1]) ans += abs(a.mn[1] - y);
        if (y > a.mx[1]) ans += abs(a.mx[1] - y);
        if (z < a.mn[2]) ans += abs(a.mn[2] - z);
        if (z > a.mx[2]) ans += abs(a.mx[2] - z);
        return ans;
    }
		
  	int ans, x, y, z;
    inline void query(int p) {
        node& t = tree[p];
        int d0 = distance(t, x, y, z), dl = inf, dr = inf;
        if (x == t.d[0] && y == t.d[1] && z == t.d[2]) d0 = inf; //cut
        ans = min(ans, d0);
        if (t.l) dl = cal(t.l, x, y, z);
        if (t.r) dr = cal(t.r, x, y, z);
        if (dl < dr){
            if (dl < ans) query(t.l);
            if (dr < ans) query(t.r);
        }
        else {
            if (dr < ans) query(t.r);
            if (dl < ans) query(t.l);
        }
    }
    inline int query(int a, int b, int c) {
        x = a; y = b; z = c;
        ans = inf;
        query(rt); 
        return ans;
    }
    
    inline int insert(int x, int y, int z, int p) {
        node& t = tree[p]; t.l = t.r = 0;
        t.mx[0] = t.mn[0] = t.d[0] = x;
        t.mx[1] = t.mn[1] = t.d[1] = y;
        t.mx[2] = t.mn[2] = t.d[2] = z;
        int now = rt, k = 0;
        while (true) {
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

int n, m, h, q;

int main() {
    scanf("%d%d%d%d", &n, &m, &h, &q);
    int op, x, y, z, cnt = 0;
    while (q--) {
        scanf("%d", &op);
        scanf("%d%d%d", &x, &y, &z);
        if (op == 1) {
            insert(x, y, z, ++cnt);
        } else {
            printf("%d\n", query(x, y, z));
        }
    }
    return 0;
}