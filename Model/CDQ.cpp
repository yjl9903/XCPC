#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a, b, sizeof(a))
using namespace std;
const int maxn = 100000 + 5;
// const int maxk = 200000 + 5;

int tree[maxn], res[maxn], n;
inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i < maxn){
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
    if (l >= r) return;
    int m = (l + r) / 2;
    cdq(l, m); cdq(m + 1, r);
    for (int i = l; i <= r; i++) b[i] = a[i];
    sort(b + l, b + m + 1, cmp2); sort(b + m + 1, b + r + 1, cmp2);
    int j = l;
    for (int i = m + 1; i <= r; i++){
        for (; j <= m && b[j].y <= b[i].y; j++) update(b[j].z, 1);
        res[b[i].id] += query(b[i].z);
    }
    for (j--; j >= l; j--) update(b[j].z, -1);
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(tree, 0); ms(res, 0);
        scanf("%d", &n);
        for (int i = 0; i < n; i++){
            scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].z);
            a[i].id = i;
        }
        sort(a, a + n, cmp1);
        cdq(0, n - 1);
        for (int i = n - 2; i >= 0; i--){
            if (a[i].x == a[i + 1].x && a[i].y == a[i + 1].y && a[i].z == a[i + 1].z)
                res[a[i].id] = res[a[i + 1].id];
        }
        for (int i = 0; i < n; i++) printf("%d\n", res[i]);
    }
    return 0;
}