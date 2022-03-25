#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000 + 5;

int n, k, x, a[maxn], vis[maxn];

int mx[maxn << 2];
void pushup(int rt){ mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]); }
void build(int l, int r, int rt){
    if (l == r){
        mx[rt] = a[l]; return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return mx[rt];
    int m = l + r >> 1, ans = 0;
    if (L <= m) ans = max(ans, query(L, R, lson));
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
}

int main(){
    scanf("%d%d%d", &n, &k, &x); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    if (k == 1 && x < n) return puts("-1"), 0;
    int tot = 1, last = 0; build(1, n, 1);
    ll ans = 0; int cnt = 0;
    while (tot + k - 1 < n){
        
    }

    return 0;
}