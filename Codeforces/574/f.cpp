#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int b[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) b[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += b[i];
    return r;
}

int n, q, tot, a[maxn], ans[maxn], x[maxn], y[maxn];
vector<PII> que[maxn];

int st[maxn], ed[maxn], vis[maxn];
map<PII,int> mp; int cid;
int gid(int x, int y) {
    if (mp.count({x, y})) return mp[{x, y}];
    return mp[{x, y}] = ++cid;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, k; i <= n; i++) {
        scanf("%d", &k);
        for (int i = 0; i < k; i++) scanf("%d%d", x + i, y + i);
        st[i] = tot + 1;
        for (int i = 0; i < k; i++) {
            int dx = x[(i + 1) % k] - x[i];
            int dy = y[(i + 1) % k] - y[i];
            int g = __gcd(abs(dx), abs(dy));
            dx /= g; dy /= g;
            a[++tot] = gid(dx, dy);
        }
        ed[i] = tot;
    }
    scanf("%d", &q);
    for (int i = 1, l, r; i <= q; i++) {
        scanf("%d%d", &l, &r);
        que[ed[r]].push_back({st[l], i});
    }
    for (int i = 1; i <= tot; i++) {
        if (vis[a[i]]) {
            update(vis[a[i]], -1);
            update(i, 1);
        } else {
            update(i, 1);
        }
        vis[a[i]] = i;
        for (auto q: que[i]) {
            ans[q.second] = query(i) - query(q.first - 1);
        }
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}