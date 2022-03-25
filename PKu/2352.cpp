#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 20000 + 5;
const int inf = 32000 + 5;

// PII p[maxn];
struct node{
    int x, y, id;
}p[maxn];
bool cmp(node a, node b){
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
vector<int> allY;
int n, ans[maxn], tree[maxn << 2];

void pushup(int rt){tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];}
void build(int l, int r, int rt){
    if (l == r) {
        tree[rt] = 0;
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int x, int l, int r, int rt){
    if (l == r){
        tree[rt] += x;
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        return tree[rt];
    }
    int m = (l + r) >> 1, ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    while (~scanf("%d", &n)){
        allY.clear();
        for (int i = 0; i < n; i++) scanf("%d%d", &p[i].x, &p[i].y), allY.push_back(p[i].y), p[i].id = i;
        sort(allY.begin(), allY.end());
        vector<int>::iterator it = unique(allY.begin(), allY.end());
        allY.resize(distance(allY.begin(), it));
        for (int i = 0; i < n; i++)
            p[i].y = lower_bound(allY.begin(), allY.end(), p[i].y) - allY.begin() + 1;
        build(1, allY.size(), 1);
        sort(p, p + n, cmp);
        int m = 0;
        for (int i = 0; i < n; i++){
            // ans[p[i].id] = query(p[i].y, 1, n, 1);
            ans[query(1, p[i].y, 1, allY.size(), 1)]++;
            update(p[i].y, 1, 1, allY.size(), 1);
        }
        for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
    }
    return 0;
}