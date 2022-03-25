#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct node{
    int a, b, c, ans = 0, sz = 1;
}f[maxn], g[maxn];
bool cmp(node& a, node& b){
    if (a.a != b.a) return a.a < b.a;
    if (a.b != b.b) return a.b < b.b;
    return a.c < b.c;
}
bool cmp1(node& a, node& b){
    if (a.b != b.b) return a.b < b.b;
    return a.c < b.c;
}

int n, k, ans[maxn], cnt[maxn];

int tree[2 * maxn] = {0};
inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i <= k){
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

void cdq(int l, int r){
    if (l >= r) return;
    int m = (l + r) >> 1;
    cdq(l, m); cdq(m + 1, r);
    sort(g + l, g + m + 1, cmp1); sort(g + m + 1, g + r + 1, cmp1);
    int j = l;
    for (int i = m + 1; i <= r; i++){
        for (; j <= m && g[j].b <= g[i].b; j++) update(g[j].c, g[j].sz);
        g[i].ans += query(g[i].c);
    }
    for (j--; j >= l; j--) update(g[j].c, -g[j].sz);
}

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d%d%d", &f[i].a, &f[i].b, &f[i].c);
    sort(f, f + n, cmp); 
    int m = 0, c = 0;
    for (int i = 0; i < n; i++){
        c++; 
        if (f[i].a != f[i + 1].a || f[i].b != f[i + 1].b || f[i].c != f[i + 1].c)
            g[++m] = f[i], g[m].sz = c, c = 0;
    }
    cdq(1, m);
    for (int i = 1; i <= m; i++){
        cnt[g[i].ans + g[i].sz - 1] += g[i].sz;
    }
    for (int i = 0; i < n; i++) printf("%d\n", cnt[i]);
    return 0;
}