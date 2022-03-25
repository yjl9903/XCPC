// HDu2665 Kth number

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

// struct node{int l, r, v;}tree[maxn * 40];
int ls[maxn * 40], rs[maxn * 40], tree[maxn * 40];
int n, q, a[maxn], root[maxn], cnt;
vector<int> h;

void build(int l, int r, int &rt){
    rt = ++cnt;
    tree[rt] = 0;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    build(l, m, ls[rt]);
    build(m + 1, r, rs[rt]);
}
void update(int p, int x, int pre, int l, int r, int &rt){
    rt = ++cnt;
    ls[rt] = ls[pre];
    rs[rt] = rs[pre];
    tree[rt] = tree[pre] + x;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    if (p <= m)
        update(p, x, ls[pre], l, m, ls[rt]);
    else
        update(p, x, rs[pre], m + 1, r, rs[rt]);
}
int query(int k, int pre, int l, int r, int rt){
    if (l == r)
        return l;
    int m = (l + r) >> 1, s = tree[ls[rt]] - tree[ls[pre]];
    if (k <= s)
        return query(k, ls[pre], l, m, ls[rt]);
    else
        return query(k - s, rs[pre], m + 1, r, rs[rt]);
}

int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        h.clear();
        cnt = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]), h.push_back(a[i]);
        sort(h.begin(), h.end());
        vector<int>::iterator it = unique(h.begin(), h.end());
        h.resize(distance(h.begin(), it));
        build(1, h.size(), root[0]);
        for (int i = 1; i <= n; i++)
            a[i] = lower_bound(h.begin(), h.end(), a[i]) - h.begin() + 1;
        for (int i = 1; i <= n; i++)
            update(a[i], 1, root[i - 1], 1, h.size(), root[i]);
        while (q--){
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            printf("%d\n", h[query(k, root[x - 1], 1, h.size(), root[y]) - 1]);
        }
    }
    return 0;
}