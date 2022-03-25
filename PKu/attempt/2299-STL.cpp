#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500000 + 5;

int a[maxn], b[maxn], tree[maxn], n;

inline int lowbit(int x) {return x & -x;}
inline void update(int i, int x){
    while (i <= n){
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
    while (~scanf("%d", &n) && n){
        ms(tree, 0);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]), b[i] = a[i];
        sort(b, b + n);
        int len = unique(b, b + n) - b;
        ll res = 0;
        for (int i = 0; i < n; i++) a[i] = lower_bound(b, b + len, a[i]) - b + 1;
        // for (int i = 0; i < n; i++) printf("%d ", a[i]); printf("\n");

        for (int i = 0; i < n; i++){
            res += i - query(a[i]);
            update(a[i], 1);
        }
        printf("%lld\n", res);
    }
    return 0;
}