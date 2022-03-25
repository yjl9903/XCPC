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
const int maxn = 200000 + 5;

int tr[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) tr[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += tr[i];
    return r;
}

struct Que {
    int x, y, z;
    int tp, id;
} q[maxn], b[maxn];

bool cmp1(Que a, Que b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}
bool cmp2(Que a, Que b) {
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

int n, m, ans[maxn];
ll xi[maxn], yi[maxn], qx[maxn], qy[maxn], w[maxn], d[maxn];
map<ll,vector<ll> > mp;

void cdq(int l, int r) {
    if (l >= r) return ;
    int m = (l + r) / 2;
    cdq(l, m);
    for (int i = l; i <= r; i++) b[i] = q[i];
    sort(b + l, b + m + 1, cmp2);
    sort(b + m + 1, b + r + 1, cmp2);
    int j = l;
    for (int i = m + 1; i <= r; i++) {
        for (; j <= m && b[j].y <= b[i].y; j++) {
            if (b[j].tp == 0) update(b[j].z, 1);
        }
        if (b[i].tp == 1) ans[b[i].id] += query(b[i].z);
    }
    for (j--; j >= l; j--) if (b[j].tp == 0) update(b[j].z, -1);
    cdq(m + 1, r);
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        mp.clear();
        scanf("%d%d", &n, &m); vector<ll> lsh;
        auto gid = [&](ll x) -> int {
            return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
        };
        for (int i = 1; i <= n; i++) {
            scanf("%lld%lld", xi + i, yi + i);
            mp[xi[i]].push_back(yi[i]);
            lsh.push_back(-xi[i]); 
            lsh.push_back(xi[i] + yi[i]);
            lsh.push_back(xi[i] - yi[i]);
        }
        for (auto& x: mp) {
            sort(x.second.begin(), x.second.end());
        }
        for (int i = 1; i <= m; i++) {
            scanf("%lld%lld%lld%lld", qx + i, qy + i, d + i, w + i);
            lsh.push_back(-qx[i] - w[i] / 2);
            lsh.push_back(qx[i] + qy[i] + d[i] / 2);
            lsh.push_back(qx[i] - qy[i] + d[i] / 2);
        }
        sort(lsh.begin(), lsh.end()); lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        for (int i = 1; i <= n; i++) {
            q[i].x = gid(-xi[i]);
            q[i].y = gid(xi[i] + yi[i]);
            q[i].z = gid(xi[i] - yi[i]);
            q[i].tp = 0; q[i].id = 0;
        }
        for (int i = 1; i <= m; i++) {
            q[i + n].x = gid(-qx[i] - w[i] / 2);
            q[i + n].y = gid(qx[i] + qy[i] + d[i] / 2);
            q[i + n].z = gid(qx[i] - qy[i] + d[i] / 2);
            q[i + n].tp = 1; q[i + n].id = i;
        }
        sort(q + 1, q + 1 + n + m, cmp1);
        cdq(1, n + m);
        lsh.clear();
        for (int i = 1; i <= n; i++) {
            lsh.push_back(xi[i]); 
            lsh.push_back(-xi[i] - yi[i]);
            lsh.push_back(-xi[i] + yi[i]);
        }
        for (int i = 1; i <= m; i++) {
            lsh.push_back(qx[i] - w[i] / 2);
            lsh.push_back(-qx[i] - qy[i] + d[i] / 2);
            lsh.push_back(-qx[i] + qy[i] + d[i] / 2);
        }
        sort(lsh.begin(), lsh.end()); lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        for (int i = 1; i <= n; i++) {
            q[i].x = gid(xi[i]);
            q[i].y = gid(-xi[i] - yi[i]);
            q[i].z = gid(-xi[i] + yi[i]);
            q[i].tp = 0; q[i].id = 0;
        }
        for (int i = 1; i <= m; i++) {
            q[i + n].x = gid(qx[i] - w[i] / 2);
            q[i + n].y = gid(-qx[i] - qy[i] + d[i] / 2);
            q[i + n].z = gid(-qx[i] + qy[i] + d[i] / 2);
            q[i + n].tp = 1; q[i + n].id = i;
        }
        sort(q + 1, q + 1 + n + m, cmp1);
        cdq(1, n + m);
        printf("Case #%d:\n", ++kase);
        for (int i = 1; i <= m; i++) {
            if (w[i] == 0 && mp.count(qx[i])) {
                int a = lower_bound(mp[qx[i]].begin(), mp[qx[i]].end(), qy[i] - d[i] / 2) - mp[qx[i]].begin() + 1;
                int b = upper_bound(mp[qx[i]].begin(), mp[qx[i]].end(), qy[i] + d[i] / 2) - mp[qx[i]].begin() + 1;
                ans[i] -= b - a;
            }
            printf("%d\n", ans[i]);
        }
        ms(tr, 0); ms(ans, 0);
    }
    return 0;
}