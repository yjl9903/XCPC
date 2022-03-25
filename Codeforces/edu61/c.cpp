#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, q, l[maxn], r[maxn], vis[maxn], cnt[maxn][3];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", l + i, r + i);
        for (int j = l[i]; j <= r[i]; j++) vis[j]++;
    }
    int ans = 0, res = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) ans++;
        if (vis[i] == 1) cnt[i][0]++;
        if (vis[i] == 2) cnt[i][1]++;
        cnt[i][0] += cnt[i - 1][0];
        cnt[i][1] += cnt[i - 1][1];
    }
    for (int i = 1; i <= q; i++) for (int j = i + 1; j <= q; j++) {
        if (r[i] < l[j] || r[j] < l[i]) {
            int tot = ans;
            tot -= cnt[r[i]][0] - cnt[l[i] - 1][0];
            tot -= cnt[r[j]][0] - cnt[l[j] - 1][0];
            res = max(res, tot);
        } else {
            int l1 = min(l[i], l[j]), l2 = max(l[i], l[j]);
            int r1 = min(r[i], r[j]), r2 = max(r[i], r[j]);
            int tot = ans;
            tot -= cnt[l2 - 1][0] - cnt[l1 - 1][0];
            tot -= cnt[r2][0] - cnt[r1][0];
            tot -= cnt[r1][0] - cnt[l2 - 1][0];
            tot -= cnt[r1][1] - cnt[l2 - 1][1];
            res = max(res, tot);
        }
    }
    cout << res << endl;
    return 0;
}