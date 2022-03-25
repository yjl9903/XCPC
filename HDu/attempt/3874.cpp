#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50000 + 5;
const int maxm = 200000 + 5;
const int maxc = 1e6 + 5;

int n, m, a[maxn], pos[maxn];
ll ans[maxm], tmp, num[maxc];
struct Ope{
    int l, r, id;
    bool operator< (const Ope& b){
        if (pos[l] == pos[b.l]) return r < b.r;
        return pos[l] < pos[b.l];
    }
}ope[maxm];

void add(int x){
    if (num[x] == 0) tmp += x;
    num[x]++;
}
void del(int x){
    num[x]--;
    if (num[x] == 0) tmp -= x;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(ans, 0); ms(num, 0);
        scanf("%d", &n);
        int sz = sqrt(1.0 * n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[i] = i / sz;
        scanf("%d", &m);
        for (int i = 0; i < m; i++){
            scanf("%d%d", &ope[i].l, &ope[i].r);
            ope[i].id = i;
        }
        sort(ope, ope + m);

        tmp = 0; int l = 0, r = 0;
        for (int i = 0; i < m; i++){
            while (l < ope[i].l) del(a[l++]);
            while (l > ope[i].l) add(a[--l]);
            while (r < ope[i].r) add(a[++r]);
            while (r > ope[i].r) del(a[r--]);
            ans[ope[i].id] = tmp;
        }
        for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);
    }
    return 0;
}