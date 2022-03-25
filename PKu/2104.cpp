#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, a[maxn], root[maxn], tree[maxn * 40], ls[maxn * 40], rs[maxn * 40], cnt = 0;
vector<int> v;

void build(int l, int r, int& rt){
    rt = ++cnt; tree[rt] = 0;
    if (l == r){
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, ls[rt]); build(m + 1, r, rs[rt]);
}
void update(int i, int x, int pre, int l, int r, int& rt){
    rt = ++cnt; ls[rt] = ls[pre]; rs[rt] = rs[pre]; tree[rt] = tree[pre] + x;
    if (l == r) {
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], l, m, ls[rt]);
    else update(i, x, rs[pre], m + 1, r, rs[rt]);
}
int query(int k, int pre, int l, int r, int rt){
    if (l == r) return l;
    int m = (l + r) >> 1, s = tree[ls[rt]] - tree[ls[pre]];
    if (k <= s) return query(k, ls[pre], l, m, ls[rt]);
    else return query(k - s, rs[pre], m + 1, r, rs[rt]);
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        v.clear(); cnt = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]), v.push_back(a[i]);
        sort(v.begin(), v.end()); vector<int>::iterator it = unique(v.begin(), v.end());
        v.resize(distance(v.begin(), it));
        int num = v.size(); build(1, v.size(), root[0]);
        for (int i = 1; i <= n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        for (int i = 1; i <= n; i++) update(a[i], 1, root[i - 1], 1, num, root[i]);
        int x, y, k;
        while (m--){
            scanf("%d%d%d", &x, &y, &k);
            printf("%d\n", v[query(k, root[x - 1], 1, num, root[y]) - 1]);
        }
    }
    return 0;
}