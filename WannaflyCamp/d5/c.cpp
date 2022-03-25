#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 400000;
const int mmp = 40;
const int sz = 2100;

// int lsh[maxn + 100], nn;
vector<int> lsh; int nn;
int gid(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    // return lower_bound(lsh, lsh + nn, x) - lsh + 1;
}

int tot, root[(int)1e5 + 5], ls[maxn * mmp], rs[maxn * mmp], cnt[maxn * mmp]; ll sum[maxn * mmp];
void update(int i, int x, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre]; cnt[rt] = cnt[pre] + 1; sum[rt] = sum[pre] + x;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson); 
}
ll query(int k, int pre, int l, int r, int rt) {
    if (cnt[rt] - cnt[pre] <= k) return sum[rt] - sum[pre];
    if (l == r) {
        ll s = sum[rt] - sum[pre], c = cnt[rt] - cnt[pre];
        return s / c * k;
    }
    int m = (l + r) >> 1;
    if (cnt[rs[rt]] - cnt[rs[pre]] >= k) return query(k, rs[pre], rson);
    else return sum[rs[rt]] - sum[rs[pre]] + query(k - cnt[rs[rt]] + cnt[rs[pre]], ls[pre], lson);
}

int n, q, a[(int)1e5 + 5], block[(int)1e5 + 3][sz + 3];
ll pre[(int)1e5 + 5];

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pre[i] = pre[i - 1] + a[i];
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        while (x) {
            if (x - x / 2 >= sz) lsh.push_back(x - x / 2);
            // lsh[nn++] = x - x / 2;
            x /= 2;
        }
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = lsh.size();
    // sort(lsh, lsh + nn);
    // nn = unique(lsh, lsh + nn) - lsh;
    for (int i = 1; i <= n; i++) {
        int x = a[i], rt = 0, pre = root[i - 1];
        while (x) {
            int y = x - x / 2;
            if (y < sz) block[i][y]++;
            else update(gid(x - x / 2), x - x / 2, pre, 1, nn, rt);
            x /= 2; pre = rt;
        }
        root[i] = rt;
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j < sz; j++) block[i][j] += block[i - 1][j];
    int l, r, k;
    while (q--) {
        scanf("%d%d%d", &l, &r, &k);
        ll x = query(k, root[l - 1], 1, nn, root[r]);
        int cc = cnt[root[r]] - cnt[root[l - 1]];
        if (k > cc) {
            k -= cc;
            for (int j = sz - 1; j >= 1 && k > 0; j--) {
                if (block[r][j] - block[l - 1][j] == 0) continue;
                if (k > block[r][j] - block[l - 1][j]) {
                    x += 1ll * j * (block[r][j] - block[l - 1][j]);
                    k -= block[r][j] - block[l - 1][j];
                } else {
                    x += 1ll * j * k;
                    k = 0;
                }
            }
        }
        printf("%lld\n", pre[r] - pre[l - 1] - x);
    }
    return 0;
}