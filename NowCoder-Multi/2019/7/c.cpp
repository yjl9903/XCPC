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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 100000 + 5;

struct tree {
    int h, c, p;
    bool operator<(const tree& b) const {
        return h < b.h;
    }
} a[maxn];

int n;

int sz, root[maxn], ls[maxn * 30], rs[maxn * 30];
ll sum[maxn * 30], cnt[maxn * 30];
void update(int i, int x, int pre, int l, int r, int& rt) {
    rt = ++sz; ls[rt] = ls[pre]; rs[rt] = rs[pre];
    cnt[rt] = cnt[pre] + x; sum[rt] = sum[pre] + 1ll * x * i;
    if (l == r) return ;
    int m = l + r >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
ll query(ll k, int l, int r, int rt) {
    if (l == r) return k * l;
    int m = l + r >> 1;
    if (k >= cnt[rt] - cnt[rs[rt]]) return sum[rt] - sum[rs[rt]] + query(k - cnt[rt] + cnt[rs[rt]], rson);
    else return query(k, lson);
}

int main() {
    while (scanf("%d", &n) == 1) {
        ll sum = 0; sz = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &a[i].h, &a[i].c, &a[i].p);
            sum += a[i].p;
        }
        sort(a + 1, a + 1 + n);
        for (int i = 1; i <= n; i++) {
            update(a[i].c, a[i].p, root[i - 1], 1, 200, root[i]);
        }
        ll ans = inf, sufcost = 0;
        for (int i = n, j; i >= 1; i = j) {
            j = i;
            ll cnt = 0, cost = 0, tot = 0;
            while (j >= 1 && a[j].h == a[i].h) {
                cnt += a[j].p;
                cost += 1ll * a[j].p * a[j].c;
                j--;
            }
            if (j && sum >= cnt + cnt) {
                // query: a[1...j], 
                tot = query(sum - cnt - cnt + 1, 1, 200, root[j]);
            }
            ans = min(ans, sufcost + tot);
            sum -= cnt; sufcost += cost;
        }
        cout << ans << '\n';
    }
    return 0;
}