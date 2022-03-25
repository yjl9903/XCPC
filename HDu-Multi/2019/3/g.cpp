#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

vector<int> lsh;
int cnt[maxn << 2];
ll sum[maxn << 2];
void build(int l, int r, int rt) {
    cnt[rt] = sum[rt] = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson); build(rson);
}
void pushup(int rt) {
    cnt[rt] = cnt[rt << 1] + cnt[rt << 1 | 1];
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void update(int i, int x, int l, int r, int rt) {
    if (l == r) {
        cnt[rt]++; sum[rt] += x;
        return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
int query(ll k, int l, int r, int rt) {
    if (l == r) {
        return min(cnt[rt], int(k / lsh[l - 1]));
    }
    int m = (l + r) / 2;
    ll s = sum[rt] - sum[rt << 1 | 1];
    if (k >= s) return cnt[rt] - cnt[rt << 1 | 1] + query(k - s, rson);
    else return query(k, lson);
}

int n, m, a[maxn], ans[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        lsh.clear();
        for (int i = 1; i <= n; i++) scanf("%d", a + i), lsh.push_back(a[i]);
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        int nn = (int)lsh.size();
        build(1, nn, 1);

        for (int i = 1; i <= n; i++) {
            int sum = query(m - a[i], 1, nn, 1);
            ans[i] = i - 1 - sum;
            int id = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
            update(id, a[i], 1, nn, 1);
        }
        for (int i = 1; i <= n; i++) {
            printf("%d ", ans[i]);
        }
        puts("");
    }
    return 0;
}