#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q, a[maxn], ans[maxn], first[maxn], last[maxn], tree[maxn];
struct Que{
    int l, r, id;
    bool operator<(const Que& b){
        if (r == b.r) return l < b.l;
        return r < b.r;
    }
};
vector<Que> v;

inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i > 0){
        tree[i] += x;
        i -= lowbit(i);
    }
}
inline int query(int i){
    int s = 0;
    while (i <= n){
        s += tree[i];
        i += lowbit(i);
    }
    return s;
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        v.clear(); ms(ans, 0); ms(first, -1); ms(tree, 0);
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            last[a[i]] = i;
            if (first[a[i]] == -1) cnt++, first[a[i]] = i;
        }
        for (int i = 0; i < q; i++){
            int l, r; scanf("%d%d", &l, &r);
            v.push_back({l, r, i});
        }
        sort(v.begin(), v.end());

        for (int i = 1, k = 0; i <= n; i++){
            while (k < q && v[k].r == i){
                int t = query(v[k].l);
                ans[v[k].id] = cnt - t;
                k++;
            }
            if (last[a[i]] == i) update(first[a[i]] - 1, 1);
        }
        
        for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
    }
    return 0;
}