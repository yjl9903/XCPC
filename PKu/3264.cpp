#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 50000 + 5;

PII val[maxn << 2];
int n, q, a[maxn];

void pushup(int rt){
    val[rt].first = max(val[rt << 1].first, val[rt << 1 | 1].first);
    val[rt].second = min(val[rt << 1].second, val[rt << 1 | 1].second);
}
void build(int l, int r, int rt){
    if (l == r){
        val[rt] = make_pair(a[l], a[l]);
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
PII query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        return val[rt];
    }
    int m = (l + r) >> 1;
    PII ans = make_pair(0, 1 << 30), t;
    if (L <= m){
        t = query(L, R, lson);
        ans.first = max(ans.first, t.first);
        ans.second = min(ans.second, t.second);
    }
    if (R > m){
        t = query(L, R, rson);
        ans.first = max(ans.first, t.first);
        ans.second = min(ans.second, t.second);
    }
    return ans;
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        build(1, n, 1);
        while (q--){
            int a, b; scanf("%d%d", &a, &b);
            PII ans = query(a, b, 1, n, 1);
            printf("%d\n", ans.first - ans.second);
        }
    }
    return 0;
}