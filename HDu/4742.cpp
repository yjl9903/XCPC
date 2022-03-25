#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;
const ll mod = 1 << 30;

PII tree[maxn], ans[maxn];
int n, res[maxn], c[maxn];
inline int lowbit(int x){return x & -x;}
inline void add(PII& a, PII& b){
    if (a.first < b.first) a = b;
    else if (a.first == b.first) a.second += b.second;
}
inline void update(int i, PII x){
    while (i < maxn){
        // tree[i] += x;
        add(tree[i], x);
        i += lowbit(i);
    }
}
inline PII query(int i){
    PII s = {0, 0};
    while (i > 0){
        // s += tree[i];
        add(s, tree[i]);
        i -= lowbit(i);
    }
    return s;
}
inline void clear(int i){
    while (i < maxn){
        tree[i] = {0, 0};
        i += lowbit(i);
    }
}

struct node{
    int x, y, z, id;
}a[maxn], b[maxn];
bool cmp1(node a, node b){
    if (a.x != b.x) return a.x < b.x;
    else if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}
bool cmp2(node a, node b){
    if (a.y == b.y) return a.z < b.z;
    return a.y < b.y;
}

void cdq(int l, int r){
    if (l == r) return ;
    int m = (l + r) / 2;
    cdq(l, m); 
    for (int i = l; i <= r; i++) b[i] = a[i];
    sort(b + l, b + m + 1, cmp2); sort(b + m + 1, b + r + 1, cmp2);
    int j = l;
    for (int i = m + 1; i <= r; i++){
        while (j <= m && b[j].y <= b[i].y) update(b[j].z, ans[b[j].id]), j++;
        // res[b[i].id] += query(b[i].z);
        PII t = query(b[i].z);
        t.first++;
        add(ans[b[i].id], t);
    }
    for (j--; j >= l; j--) clear(b[j].z);
    cdq(m + 1, r);
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(tree, 0); ms(res, 0); 
        scanf("%d", &n); fill(ans, ans + n, make_pair(1, 1));
        for (int i = 0; i < n; i++){
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
            c[i] = a[i].z;
            a[i].id = i;
        }
        sort(c, c + n);
        int len = unique(c, c + n) - c;
        for (int i = 0; i < n; i++) a[i].z = lower_bound(c, c + len, a[i].z) - c + 1;
        sort(a, a + n, cmp1);
        cdq(0, n - 1);
        // for (int i = 0; i < n; i++) printf("%d ", res[i]); printf("\n");
        // printf("%d %d\n", lis(), countLis());
        PII res = make_pair(0, 0);
        for (int i = 0; i < n; i++) add(res, ans[i]);
        printf("%d %d\n", res.first, res.second);
    }
    return 0;
}