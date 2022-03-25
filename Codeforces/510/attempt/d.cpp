#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

ll t, n, a[maxn] = {0};
vector<ll> v;

int tot, ls[maxn * 40], rs[maxn * 40], root[maxn], sum[maxn * 40];

void update(int i, int x, int pre, int l, int r, int &rt){
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre]; sum[rt] = sum[pre] + x;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
int query(int k, int pre, int l, int r, int rt){
    if (l == r) return sum[rt] - sum[pre];
    int m = (l + r) >> 1;
    if (k <= m) return query(k, ls[pre], lson);
    else return sum[ls[rt]] - sum[ls[pre]] + query(k, rs[pre], rson);
}

int main(){
    scanf("%I64d%I64d", &n, &t);
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i), a[i] += a[i - 1], v.push_back(a[i]);
    sort(v.begin(), v.end()); 
    auto it = unique(v.begin(), v.end()); 
    v.resize(distance(v.begin(), it));

    for (int i = 1; i <= n; i++){
        int pos = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        update(pos, 1, root[i - 1], 1, v.size(), root[i]);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++){
        int tag = lower_bound(v.begin(), v.end(), a[i - 1] + t) - v.begin();
        if (tag == 0) continue;
        ans += query(tag, root[i - 1], 1, v.size(), root[n]);
    }
    printf("%I64d", ans);
    return 0;
}