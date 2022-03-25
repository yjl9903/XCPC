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
const int maxn = 100000 + 5;

int n, a[maxn];

struct Node {
    int val, cnt;
    void clear() {
        val = inf; cnt = 0;
    }
    Node operator+(const Node& b) const {
        if (val == b.val) return (Node){ val, cnt + b.cnt };
        else if (val < b.val) return (Node){ val, cnt };
        else return (Node){ b.val, b.cnt };
    }
    Node operator+=(const int& b) {
        val += b;
    }
} b[maxn * 4];
int tag[maxn * 4];
void build(int l, int r, int rt) {
    b[rt].clear(); tag[rt] = 0;
    if (l == r) {
        b[rt].cnt = 1; return ;     
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
}
void pushdown(int rt) {
    if (!tag[rt]) return ;
    int& t = tag[rt];
    b[rt << 1] += t;
    tag[rt << 1] += t;
    b[rt << 1 | 1] += t;
    tag[rt << 1 | 1] += t;
    t = 0;
}
void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
        b[rt] += x; tag[rt] += x;
        return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    b[rt] = b[rt << 1] + b[rt << 1 | 1];
}

void print(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
        dbg(l, b[rt].val);
        return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    print(lson); print(rson);
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        build(1, n, 1);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }
        ll ans = 0;
        map<int,int> last;
        vector<int> stmn, stmx;
        for (int i = 1; i <= n; i++) {
            update(i, i, -inf);
            int q = i, tot = 0;
            while (!stmn.empty() && a[stmn.back()] >= a[i]) {
                int p = stmn.back(); stmn.pop_back();
                update(p + 1, q, tot - a[i]);
                q = p; tot = a[p];
            }
            if (!stmn.empty()) {
                int p = stmn.back();
                update(p + 1, q, tot - a[i]);
            } else {
                update(1, q, tot - a[i]);
            }
            q = i; tot = 0;
            while (!stmx.empty() && a[stmx.back()] <= a[i]) {
                int p = stmx.back(); stmx.pop_back();
                update(p + 1, q, a[i] - tot);
                q = p; tot = a[p];
            }
            if (!stmx.empty()) {
                int p = stmx.back();
                update(p + 1, q, a[i] - tot);
            } else {
                update(1, q, a[i] - tot);
            }

            stmn.push_back(i);
            stmx.push_back(i);
            update(last[a[i]] + 1, i, -1);
            last[a[i]] = i;

            if (b[1].val == -1) ans += b[1].cnt;
        }
        printf("Case #%d: %lld\n", ++kase, ans);
    }    
    return 0;
}