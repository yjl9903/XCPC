#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <functional>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, a[maxn], root[maxn << 1];

namespace SegTrees {
    const int maxm = maxn * 40;
    int tot, ls[maxm], rs[maxm], cnt[maxm];
    ll sum[maxm];
    void update(int i, int l, int r, int& rt) {
        if (!rt) rt = ++tot;
        if (l == r) {
            cnt[rt] = 1; sum[rt] = l;
            return ;
        }
        int m = (l + r) / 2;
        if (i <= m) update(i, l, m, ls[rt]);
        else update(i, m + 1, r, rs[rt]);
        cnt[rt] = cnt[ls[rt]] + cnt[rs[rt]];
        sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    }
    int join(int x, int y, int l, int r) {
        if (!x || !y) return x + y;
        int u = ++tot;
        if (l == r) {
            cnt[u] = cnt[x] + cnt[y];
            sum[u] = sum[x] + sum[y];
        } else {
            int m = (l + r) / 2;
            ls[u] = join(ls[x], ls[y], l, m);
            rs[u] = join(rs[x], rs[y], m + 1, r);
            cnt[u] = cnt[ls[u]] + cnt[rs[u]];
            sum[u] = sum[ls[u]] + sum[rs[u]];
        }
        return u;
    }
    int query(int L, int R, int l, int r, int rt) {
        if (!rt) return 0;
        if (L <= l && r <= R) return cnt[rt];
        int m = (l + r) / 2, ans = 0;
        if (L <= m) ans += query(L, R, l, m, ls[rt]);
        if (R > m) ans += query(L, R, m + 1, r, rs[rt]);
        return ans;
    }
    ll querysum(int L, int R, int l, int r, int rt) {
        if (!rt) return 0;
        if (L <= l && r <= R) return sum[rt];
        int m = (l + r) / 2; ll ans = 0;
        if (L <= m) ans += querysum(L, R, l, m, ls[rt]);
        if (R > m) ans += querysum(L, R, m + 1, r, rs[rt]);
        return ans;
    }
    vector<int> query(int rt) {
        vector<int> ans;
        function<void(int,int,int)> que = [&](int l, int r, int rt) {
            if (!rt) return ;
            if (!cnt[rt]) return ;
            if (l == r) {
                ans.push_back(l); return ;
            }
            int m = (l + r) / 2;
            que(l, m, ls[rt]); que(m + 1, r, rs[rt]);
        };
        que(1, n, rt);
        return ans;
    }
}

namespace sam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1];
    map<int,int> ch[maxn << 1];
    void clear() { 
        tot = last = 1; ch[1].clear();
    }
    int insert(int c) {
        int cur = ++tot, p = last; 
        ch[cur].clear();
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p].count(c); p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                ch[nq] = ch[q];
                for (; ch[p].count(c) && ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void build() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
    }
    ll cal(int u, int v) {
        ll ans = 0;
        int mx = len[u], mn = len[link[u]];
        if (SegTrees::cnt[root[u]] > SegTrees::cnt[root[v]]) swap(u, v);
        vector<int> endpos = SegTrees::query(root[u]);
        for (auto& pos: endpos) {
            int ql = pos + mx + 1, qr = n;
            if (ql <= qr) ans += 1ll * mx * SegTrees::query(ql, qr, 1, n, root[v]);
            ql = 1, qr = pos - mx - 1;
            if (ql <= qr) ans += 1ll * mx * SegTrees::query(ql, qr, 1, n, root[v]);
            
            ql = pos + 1, qr = pos + mx;
            if (ql <= qr) {
                int c = SegTrees::query(ql, qr, 1, n, root[v]);
                ll s = SegTrees::querysum(ql, qr, 1, n, root[v]);
                ans += s - 1ll * c * (pos + 1);
            }

            ql = pos - mx, qr = pos - 1;
            if (ql <= qr) {
                int c = SegTrees::query(ql, qr, 1, n, root[v]);
                ll s = SegTrees::querysum(ql, qr, 1, n, root[v]);
                ans += 1ll * c * (pos - 1) - s;
            }
        }
        return ans;
    }
    ll solve() {
        build();
        ll ans = 0;
        for (int i = tot; i >= 2; i--) {
            int v = a[i], u = link[v];
            ans += cal(u, v);
            root[u] = SegTrees::join(root[u], root[v], 1, n);
        }
        return ans;
    }
}

int main() {
    sam::clear();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    n--;
    for (int i = 1; i <= n; i++) {
        int u = sam::insert(a[i + 1] - a[i]);
        SegTrees::update(i, 1, n, root[u]);
    }
    cout << sam::solve() + 1ll * n * (n + 1) / 2;
    return 0;
}