#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int tree[maxn];
inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x = 1) {
    while (i < maxn) {
        tree[i] += x; i += lowbit(i);
    }
}
inline int query(int i) {
    int r = 0; while (i > 0) r += tree[i], i -= lowbit(i);
    return r;
}

vector<int> lsh;
int gid(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}
int n, m, a[maxn], b[maxn];

ll cal(int y) {
    lsh.clear(); for (int i = 1; i <= n; i++) lsh.push_back(b[i] ^ y);
    sort(lsh.begin(), lsh.end()); lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        int id = gid(b[i] ^ y);
        ans += query(id);
        update(id);
    }
    ms(tree, 0);
    return ans;
}
int get(int k) {
    int h = m >> (k + 1);
    int ans = (m >> (k + 1)) * (1 << k);
    int x = (h << (k + 1)) | (1 << k);
    if (m >= x) ans += (m & ((1 << k) - 1)) + 1;
    return ans;
}

int main(){
    // int cnt = 0, m = 10, k = 1;
    // for (int i = 0; i <= m; i++) if (i & (1 << k)) cnt++;
    // cout << cnt << ' ' << (m >> (k + 1)) * (1 << k) + (m & ((1 << k) - 1)) + 1) << endl;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    int fi = cal(0), ans = 0, ans1 = 0;

    for (int i = 1; i <= m; i++) ans1 += cal(i);
    
    for (int i = 0; (i << i) <= m; i++) {
        int t = cal(1 << i) - fi;
        ans += get(i) * t;
    }
    cout << ans << endl;
    return 0;
}