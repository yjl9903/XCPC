#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, a[maxn];

#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
int tot, root[maxn], ls[maxn * 40], rs[maxn * 40], cnt[maxn * 40];
void update(int i, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre]; cnt[rt] = cnt[pre] + 1;
    if (l == r) return ;
    int m = (l + r) / 2;
    if (i <= m) update(i, ls[pre], lson);
    else update(i, rs[pre], rson);
}
int query(int k, int pre, int l, int r, int rt) {
    if (l == r) return l;
    int m = (l + r) / 2, sum = cnt[ls[rt]] - cnt[ls[pre]];
    if (k <= sum) return query(k, ls[pre], lson);
    else return query(k - sum, rs[pre], rson);
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        tot = 0; vector<int> lsh;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i); lsh.push_back(a[i]);
        }
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        int nn = (int)lsh.size();
        for (int i = 1; i <= n; i++) {
            int x = lsh.end() - lower_bound(lsh.begin(), lsh.end(), a[i]);
            // dbg(x, a[i]);
            update(x, root[i - 1], 1, nn, root[i]);
        }
        int l, r;
        auto f = [&](int id) -> int {
            return lsh[(int)lsh.size() - id];
        };
        while (q--) {
            scanf("%d%d", &l, &r);
            if (r - l + 1 < 3) {
                puts("-1"); continue;
            }
            vector<int> v;
            v.push_back(f(query(1, root[l - 1], 1, nn, root[r])));
            v.push_back(f(query(2, root[l - 1], 1, nn, root[r])));
            v.push_back(f(query(3, root[l - 1], 1, nn, root[r])));
            int k = 4;
            while (k <= r - l + 1 && v[1] + v[2] <= v[0]) {
                int x = f(query(k, root[l - 1], 1, nn, root[r]));
                v[0] = v[1]; v[1] = v[2]; v[2] = x; k++;
            }
            if (v[1] + v[2] > v[0]) {
                ll ans = v[0]; ans += v[1]; ans += v[2];
                printf("%lld\n", ans);
            } else {
                puts("-1");
            }
        }
    }
    return 0;
}