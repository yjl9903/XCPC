#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, x[maxn], y[maxn];
vector<int> v;

struct bit{
    int tree[maxn];
    bit(){ms(tree, 0);}
    inline int lowbit(int x){return x & -x;}
    inline void update(int i, int x){
        while (i < maxn){
            tree[i] = max(x, tree[i]);
            i += lowbit(i);
        }
    }
    inline int query(int i){
        int r = tree[i];
        while (i > 0){
            r = max(r, tree[i]);
            i -= lowbit(i);
        }
        return r;
    }
} a, b;

inline int id(int x){
    return v.size() - (lower_bound(v.begin(), v.end(), x) - v.begin());
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d%d", x + i, y + i);
        v.push_back(x[i]);
        v.push_back(y[i]);
    }
    sort(v.begin(), v.end());
    auto it = unique(v.begin(), v.end());
    v.resize(distance(v.begin(), it));
    ll ans = 0;
    for (int i = n - 1; i >= 0; i--){
        int h = a.query(id(x[i]));
        int w = b.query(id(y[i]));
        ans += x[i] + y[i] - h - w;
        a.update(id(x[i]), y[i]);
        b.update(id(y[i]), x[i]);
    }
    printf("%lld\n", ans);
    return 0;
}