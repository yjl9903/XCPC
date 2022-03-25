#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10000 + 5;

int n, len[maxn], tree[maxn * 10], lazy[maxn * 10];
PII a[maxn];
vector<int> v;

void pushup(int rt){
    if (tree[rt << 1] == tree[rt << 1 | 1]) tree[rt] = tree[rt << 1];
    else tree[rt] = -1;
}
void pushdown(int rt){
    if (lazy[rt] == -1) return;
    tree[rt << 1] = tree[rt << 1 | 1] = lazy[rt];
    lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
    lazy[rt] = -1;
}
void update(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R && tree[rt] != -1){
        // printf("%d %d %d\n", )
        len[tree[rt]] -= r - l + 1;
        tree[rt] = x; lazy[rt] = x;
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n); v.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].first, &a[i].second);
            v.push_back(a[i].first); v.push_back(a[i].second);
        }
        sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin());
        ms(tree, 0); ms(lazy, -1);
        for (int i = 1; i <= n; i++){
            a[i].first = lower_bound(v.begin(), v.end(), a[i].first) - v.begin() + 1;
            a[i].second = lower_bound(v.begin(), v.end(), a[i].second) - v.begin() + 1;
            update(a[i].first, a[i].second, i, 1, v.size(), 1);
            len[i] = a[i].second - a[i].first + 1;
            // printf("+ %d %d\n", a[i].first, a[i].second);
        }
        int ans = 0;
        // for (int i = 1; i <= n; i++) printf("%d\n", len[i]);
        for (int i = 1; i <= n; i++) if (len[i] > 0) ans++;
        printf("%d\n", ans);
    }
    return 0;
}