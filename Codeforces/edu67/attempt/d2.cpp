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

int c[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) c[i] += x;
}
void update(int l, int r, int x) {
    update(l, x); update(r + 1, -x);
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += c[i];
    return r;
}

int n;
PII a[maxn], b[maxn];

int mx[maxn << 2];
void build(int l, int r, int rt) {
    if (l == r) {
        mx[rt] = a[l].first; return ;
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
    int m = (l + r) / 2; int ans = 0;
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
            scanf("%d", &a[i].first), a[i].second = i;
            v1.push_back(a[i].first);
            mp[a[i].first].push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", &b[i].first), b[i].second = i;
            v2.push_back(b[i].first);
        }
        sort(v1.begin(), v1.end()); sort(v2.begin(), v2.end());
        if (v1 != v2) {
            puts("NO"); continue;
        }
        // sort(a + 1, a + 1 + n); 
        // sort(b + 1, b + 1 + n);
        build(1, n, 1);
        int flag = 0;
        vector<PII> op;
        for (int i = n; i >= 1; i--) {
            auto it = mp[b[i].first].end(); it--;
            int tag = *it; mp[b[i].first].erase(it);
            int offset = query(tag);
            int from = tag - offset, to = i;
            // if (from > to) {
            //     flag = 1; break;
            // }
            // if (from == to) {
            //     update(tag, 1, n, 1);
            //     continue;
            // }
            if (tag < i) {
                // int mx = query(tag, i, 1, n, 1);
                int mx = query(tag, n, 1, n, 1);
                // dbg(tag, i, n - offset, mx);
                if (mx > a[tag].first) {
                    // dbg(mx, tag, a[tag].first);
                    flag = 1; break;
                }
            }
            // dbg(from, to);
            int l = tag + 1, r = tag + to - from + n - i - offset;
            // op.push_back({l, r}); update(l, r, 1);
            update(tag, 1, n, 1);
        }
        if (flag) puts("NO");
        else puts("YES");
        for (auto& x: op) update(x.first, x.second, -1);
    }
    return 0;
}