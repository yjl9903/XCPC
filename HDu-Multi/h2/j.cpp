#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, x, y, tree[maxn], a[maxn];
vector<int> v;

inline int lowbit(int x) {return x & -x;}
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

int main(){
    while (~scanf("%d%d%d", &n, &x, &y)){
        v.clear(); ms(tree, 0);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]), v.push_back(a[i]);
        sort(v.begin(), v.end());
        vector<int>::iterator it = unique(v.begin(), v.end());
        v.resize(distance(v.begin(), it));
        for (int i = 1; i <= n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        ll ans = 0;
        for (int i = 1; i <= n; i++){
            ans += 1ll * (i - 1 - query(a[i]));
            update(a[i], 1);
        }
        if (x <= y) printf("%lld\n", 1ll * ans * x);
        else printf("%lld\n", 1ll * ans * y);
    }
    return 0;
}