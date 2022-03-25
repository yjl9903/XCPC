#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n; vector<int> v;
struct node{
    int x, y, v;
}a[maxn];
bool cmp(node& a, node& b){
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y > b.y;
    return a.v < b.v;
}

int tree[maxn];
inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i < maxn){
        tree[i] = max(tree[i], x);
        i += lowbit(i);
    }
}
inline int query(int i){
    int s = 0;
    while (i > 0){
        s = max(s, tree[i]);
        i -= lowbit(i);
    }
    return s;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        v.clear(); ms(tree, 0);
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].v);
            v.push_back(a[i].y);
        }
        sort(a, a + n, cmp); 
        sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
        int ans = 0;
        for (int i = 0; i < n; i++){
            int pos = lower_bound(v.begin(), v.end(), a[i].y) - v.begin() + 1;
            int tmp = query(pos - 1) + a[i].v;
            update(pos, tmp);
            ans = max(ans, tmp);
        }
        printf("%d\n", ans);
    }
    return 0;
}