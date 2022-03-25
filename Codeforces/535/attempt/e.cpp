#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, m, a[maxn], mx[maxn << 2], mn[maxn << 2], cnt[maxn << 2], tag[maxn << 2], allmx = 0;

void pushup(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
    // cnt[rt] = cnt[rt << 1] + cnt[rt << 1 | 1];
    if (mx[rt << 1] == allmx) cnt[rt] += cnt[rt << 1];
    if (mx[rt << 1 | 1] == allmx) cnt[rt] += cnt[rt << 1 | 1];
}
void pushdown(int rt) {
    if (!tag[rt]) return;
    mx[rt << 1] -= tag[rt]; mx[rt << 1 | 1] -= tag[rt];
    mn[rt << 1] -= tag[rt]; mn[rt << 1 | 1] -= tag[rt];
    tag[rt << 1] += tag[rt]; tag[rt << 1 | 1] += tag[rt];
    tag[rt] = 0;
}
void build(int l, int r, int rt) {
    if (l == r) {
        mx[rt] = mn[rt] = a[l]; allmx = max(allmx, a[l]);
        return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt) {

}

int main(){
    scanf("%d%d", &n, &m); 
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int allmx = 0, allmn = 1e9, mxcnt = 0, mncnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > allmx) allmx = a[i], mxcnt = 1;
        else if (a[i] == allmx) mxcnt++;
        if (a[i] < allmn) allmn = a[i], mncnt = 1;
        else if (a[i] == allmn) mncnt++;
    }
    vector<int> v; int l, r;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &l, &r);
        int f1 = 0, f2 = 0, flag = 1;
        for (int i = l; i <= r; i++) {
            if (a[i] == allmx) f1++;
            if (a[i] == allmn) f2++;
        }
        if (f2 || f1 != mxcnt) {
            for (int i = l; i <= r; i++) a[i]--;
            allmx = 0, allmn = 1e9, mxcnt = 0, mncnt = 0;
            for (int i = 1; i <= n; i++) {
                if (a[i] > allmx) allmx = a[i], mxcnt = 1;
                else if (a[i] == allmx) mxcnt++;
                if (a[i] < allmn) allmn = a[i], mncnt = 1;
                else if (a[i] == allmn) mncnt++;
            }
            v.push_back(i);
        }
    }
    printf("%d\n%d\n", allmx - allmn, v.size());
    for (int& x: v) printf("%d ", x);
    return 0;
}