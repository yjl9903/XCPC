#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int inf = 1 << 20;

int n, m, k, a[maxn] = {0}, sz;
ll ans[maxn], tmp = 0, cnt[inf] = {0};
struct Que{int l, r, id;}que[maxn];
bool cmp(Que a, Que b){
    if (a.l / sz != b.l / sz) return a.l < b.l;
    return a.r < b.r;
}

void add(int x){
    tmp += cnt[x ^ k];
    cnt[x]++;
}
void del(int x){
    cnt[x]--;
    tmp -= cnt[x ^ k];
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    sz = sqrt(n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] ^= a[i - 1];
    for (int i = 1; i <= m; i++) scanf("%d%d", &que[i].l, &que[i].r), que[i].id = i;
    sort(que + 1, que + m + 1, cmp);

    cnt[0] = 1;
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++){
        while (l < que[i].l) del(a[l++ - 1]);
        while (l > que[i].l) add(a[--l - 1]);
        while (r < que[i].r) add(a[++r]);
        while (r > que[i].r) del(a[r--]);
        ans[que[i].id] = tmp;
    }
    for (int i = 1; i <= m; i++) printf("%I64d\n", ans[i]);
    return 0;
}

/* 
http://www.codeforces.com/contest/620/problem/F
http://www.codeforces.com/contest/617/problem/E
http://codeforces.com/contest/633/problem/H
小z的袜子
*/