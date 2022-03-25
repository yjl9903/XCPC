#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 600000 + 5;

int n, a[maxn], b[maxn];

int mx[maxn << 2];
void build(int l, int r, int rt) {
    if (l == r) {
        mx[rt] = a[l]; return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void update(int i, int l, int r, int rt) {
    if (l == r) {
        mx[rt] = -1; return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, lson);
    else update(i, rson);
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
int query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return mx[rt];
    int m = (l + r) / 2; int ans = -1;
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector<int> v1, v2;
        map<int, vector<int> > mp;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            v1.push_back(a[i]);
            mp[a[i]].push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", b + i);
            v2.push_back(b[i]);
        }
        sort(v1.begin(), v1.end()); sort(v2.begin(), v2.end());
        if (v1 != v2) {
            puts("NO"); continue;
        }
        build(1, n, 1);
        int flag = 0;
        for (int i = n; i >= 1; i--) {
            auto it = mp[b[i]].end(); it--;
            int tag = *it; mp[b[i]].erase(it);
            int mx = query(tag, n, 1, n, 1);
            if (mx > b[i]) flag = 1;
            update(tag, 1, n, 1);
        }
        if (flag) puts("NO");
        else puts("YES");
    }
    return 0;
}