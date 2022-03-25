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
const int inf = 1 << 30;
const int maxn = 400000 + 5;

ll ans;
vector<int> lsh;
int n, m, uu[maxn], vv[maxn], ql[maxn], qr[maxn];

namespace dsu {
    int pre[maxn], siz[maxn];
    vector<PII> sta;
    void init() {
        sta.clear();
        for (int i = 1; i <= n; i++) {
            pre[i] = i; siz[i] = 1;
        }
    }
    int find(int x) {
        while (x != pre[x]) x = pre[x]; return x;
    }
    bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        if (siz[x] > siz[y]) swap(x, y);
        pre[x] = y; siz[y] += siz[x];
        sta.push_back({x, y});
        return 1;
    }
    void undo() {
        PII tp = sta.back(); sta.pop_back();
        int x = tp.first, y = tp.second;
        pre[x] = x; siz[y] -= siz[x];
    }
}

vector<PII> nodes[maxn << 2];
void update(int L, int R, PII x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        nodes[rt].push_back(x); return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
}
void dfs(int l, int r, int rt) {
    int cnt = 0;
    for (auto& x: nodes[rt]) if (dsu::join(x.first, x.second)) cnt++;
    if (l == r) {
        if (dsu::find(1) == dsu::find(n)) {
            // cout << "solve: " << l << endl;
            ans += lsh[r] - lsh[l - 1];
        }
        for (int i = 0; i < cnt; i++) dsu::undo();
        return ;
    }
    int m = (l + r) / 2;
    dfs(lson); dfs(rson);
    for (int i = 0; i < cnt; i++) dsu::undo();
}

int main() {
    scanf("%d%d", &n, &m);
    dsu::init();
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", uu + i, vv + i, ql + i, qr + i);
        lsh.push_back(ql[i]);
        lsh.push_back(qr[i] + 1);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    int nn = (int)lsh.size();
    for (int i = 1; i <= m; i++) {
        int tl, tr;
        tl = lower_bound(lsh.begin(), lsh.end(), ql[i]) - lsh.begin() + 1;
        tr = lower_bound(lsh.begin(), lsh.end(), qr[i] + 1) - lsh.begin() + 1;
        update(tl, tr - 1, { uu[i], vv[i] }, 1, nn, 1);
    }
    dfs(1, nn, 1);
    cout << ans;
    return 0;
}