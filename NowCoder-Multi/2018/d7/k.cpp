#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
#include <stack>
#define get_min(a,b) a = min (a, b)
#define get_max(a,b) a = max (a, b);
using namespace std;
#define maxn 100005

struct node {
    int d[2], l, r, c;//节点的点的坐标 左右孩子
    long long Max[2], Min[2];//节点中点x的最值 y的最值
    int id;
}tree[maxn<<1], tmp;
int n, m;
int root, cmp_d;

bool cmp (const node &a, const node &b) {
    return a.d[cmp_d] < b.d[cmp_d] || (a.d[cmp_d] == b.d[cmp_d] &&
            a.d[cmp_d^1] < b.d[cmp_d^1]);
}

void push_up (int p, int pp) {
    get_min (tree[p].Min[0], tree[pp].Min[0]);
    get_min (tree[p].Min[1], tree[pp].Min[1]);
    get_max (tree[p].Max[0], tree[pp].Max[0]);
    get_max (tree[p].Max[1], tree[pp].Max[1]);
}

int build_tree (int l, int r, int D) {
    int mid = (l+r)>>1;
    tree[mid].l = tree[mid].r = 0;
    cmp_d = D;
    nth_element (tree+l+1, tree+mid+1, tree+1+r, cmp);
    //按照cmp把第mid元素放在中间 比他小的放左边 比他大的放右边
    tree[mid].Max[0] = tree[mid].Min[0] = tree[mid].d[0];
    tree[mid].Max[1] = tree[mid].Min[1] = tree[mid].d[1];
    if (l != mid) tree[mid].l = build_tree (l, mid-1, D^1);
    if (r != mid) tree[mid].r = build_tree (mid+1, r, D^1);
    if (tree[mid].l) push_up (mid, tree[mid].l);
    if (tree[mid].r) push_up (mid, tree[mid].r);
    return mid;
}

void insert (int now) {
    int D = 0, p = root;
    while (1) {
        push_up (p, now);//先更新p节点
        if (tree[now].d[D] >= tree[p].d[D]) {
            if (!tree[p].r) {
                tree[p].r = now;
                return ;
            }
            else p = tree[p].r;
        }
        else {
            if (!tree[p].l) {
                tree[p].l = now;
                return ;
            }
            else p = tree[p].l;
        }
        D ^= 1;
    }
    return ;
}

#define INF 4e18
#define sqr(a) (a)*(a)
long long ans, x, y;
int tc, ansp;
long long dis (int p, int x, int y) {//点(x,y)在p的管辖范围内的可能最小值
    long long ans = 0;
    if (x < tree[p].Min[0]) ans += sqr (tree[p].Min[0]-x);
    if (x > tree[p].Max[0]) ans += sqr (x-tree[p].Max[0]);
    if (y < tree[p].Min[1]) ans += sqr (tree[p].Min[1]-y);
    if (y > tree[p].Max[1]) ans += sqr (y-tree[p].Max[1]);
    return ans;
}

long long distance (int i, long long x, long long y) {
    long long xx = tree[i].d[0]-x, yy = tree[i].d[1]-y;
    return (xx*xx+yy*yy);
}

void query (int p) {
    long long dl = INF, dr = INF, d0;
    d0 = distance (p, x, y);//初始答案
    // if (tree[p].d[0] == x && tree[p].d[1] == y) d0 = INF;//重合
    if (tree[p].c > tc) d0 = INF;
    // get_min (ans, d0);
    if (d0 <= ans){
        if (ans == d0){
            if (tree[p].id < ansp) ansp = tree[p].id;
        }
        else ansp = tree[p].id;
        ans = d0;
    }
    if (tree[p].l) dl = dis (tree[p].l, x, y);
    if (tree[p].r) dr = dis (tree[p].r, x, y);
    if (dl < dr) {
        if (dl < ans) query (tree[p].l);
        if (dr < ans) query (tree[p].r);
    }
    else {
        if (dr < ans) query (tree[p].r);
        if (dl < ans) query (tree[p].l);
    }
}

// long long res[maxn];

int main () {
    // int t; cin >> t;
    // while (t--) {
    //     scan (n);
    //     for (int i = 1; i <= n; i++) {
    //         scan (tree[i].d[0]);
    //         scan (tree[i].d[1]);
    //         tree[i].id = i;
    //     }
    //     root = build_tree (1, n, 0);
    //     for (int i = 1; i <= n; i++) {
    //         ans = INF;
    //         x = tree[i].d[0], y = tree[i].d[1];
    //         query (root);
    //         res[tree[i].id] = ans;
    //     }
    //     for (int i = 1; i <= n; i++) printf ("%lld\n", res[i]);
    // }
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++){
            scanf("%d%d%d", &tree[i].d[0], &tree[i].d[1], &tree[i].c);
            tree[i].id = i;
        }
        root = build_tree(1, n, 0);
        for (int i = 1; i <= m; i++){
            ans = INF; ansp = 0; scanf("%d%d%d", &x, &y, &tc); 
            query(root);
            printf("%d %d %d\n", tree[ansp].d[0], tree[ansp].d[1], tree[ansp].c);
        }
    }
    return 0;
}