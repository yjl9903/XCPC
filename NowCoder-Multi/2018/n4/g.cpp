#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n, m, a[maxn];
ll tree[maxn][2];
map<int,int> mp;
map<int,int>::iterator it;

inline int lowbit(int x){return x & -x;}
inline void update(int i, int x, int t = 0){
    while (i > 0){
        tree[i][t] += x;
        i -= lowbit(i);
    }
}
inline ll query(int i, int t = 0){
    ll s = 0;
    while (i < maxn){
        s += tree[i][t];
        i += lowbit(i);
    }
    return s;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        mp.clear(); ms(tree, 0);
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]), mp[a[i]]++;
        for (it = mp.begin(); it != mp.end(); it++){
            update(it -> second, it -> second);
            update(it -> second, 1, 1);
        }
        int res = -1;
        for (it = mp.end();;){
            it--;
            int sum = query(it -> second) - it -> second;
            int cnt = query(it -> second, 1) - 1;
            sum -= (it -> second - 1) * cnt;
            // printf("%d %d\n", it -> first, sum);
            if (m >= sum){
                res = it -> first;
                break;
            }
            if (it == mp.begin()) break;
        }
        printf("%d\n", res);
    }
    return 0;
}