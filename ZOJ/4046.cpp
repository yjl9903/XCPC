#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int tree[maxn];
inline int lowbit(int x){return x & -x;}
inline void update(int i){
    while (i < maxn){
        tree[i]++; i += lowbit(i);
    }
}
inline int query(int i){
    int r = 0;
    while (i){
        r += tree[i]; i -= lowbit(i);
    }
    return r;
}

int n, a[maxn], pos[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(tree, 0);
        scanf("%d", &n); ll tot = 0, ans = 0;
        for (int i = 1; i <= n; i++){
            scanf("%d", &a[i]); pos[a[i]] = i;
            tot += i - query(a[i]) - 1;
            update(a[i]);
        }
        ans = tot;
        for (int i = n; i > 1; i--){
            tot += 2 * pos[i] - n - 1;
            ans = min(ans, tot);
        }
        printf("%lld\n", ans);
    }
    return 0;
}