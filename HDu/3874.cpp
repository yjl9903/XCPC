#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50000 + 5;
const int maxm = 200000 + 5;
const int inf = 1000000 + 5;

int n, m, a[maxn], last[inf];
ll ans[maxm], tree[inf];
struct Ope{int l, r, id;}ope[maxm];
bool cmp(Ope a, Ope b){
    if (a.r == b.r) return a.l < b.l;
    return a.r < b.r;
}
inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i < inf){
        tree[i] += x;
        i += lowbit(i);
    }
}
inline int query(int i){
    int s = 0;
    while (i > 0){
        s += tree[i];
        i -= lowbit(i);
    }
    return s;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(ans, 0); ms(last, 0); ms(tree, 0); 
        scanf("%d", &n); 
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        scanf("%d", &m);
        for (int i = 0; i < m; i++){
            scanf("%d%d", &ope[i].l, &ope[i].r); 
            ope[i].id = i;
        }
        sort(ope, ope + m, cmp);
        int k = 0;
        ll s = 0;
        for (int i = 1; i <= inf && k < m; i++){
            // printf("%d %lld\n", i, s);
            if (last[a[i]]){
                update(last[a[i]], -a[i]);
                last[a[i]] = i;
                update(i, a[i]);
            }
            else {
                last[a[i]] = i;
                s += a[i];
                update(i, a[i]);
            }
            while (k < m && ope[k].r == i){
                ll t = query(ope[k].l - 1);
                ans[ope[k].id] = s - t;
                k++;
            }
        }
        for (int i = 0; i < m; i++){
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}