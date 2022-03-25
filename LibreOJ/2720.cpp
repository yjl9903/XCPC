#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

char s[maxn];
int n, q, dep[maxn];

namespace SegTrees {
    const int maxm = maxn * 60;
    int tot, root[maxn << 1], ls[maxm], rs[maxm], val[maxm];
    void update(int i, int l, int r, int& rt) {
        if (!rt) rt = ++tot, ls[rt] = rs[rt] = val[rt] = 0;
        if (l == r) {
            val[rt]++; return ;
        }
        int m = (l + r) / 2;
        if (i <= m) update(i, l, m, ls[rt]);
        else update(i, m + 1, r, rs[rt]);
        val[rt] = val[ls[rt]] + val[rs[rt]];
    }
    int join(int x, int y, int l = 1, int r = n) {
        if (!x || !y) return x + y;
        int u = ++tot; ls[u] = rs[u] = val[u] = 0;
        if (l == r) {
            val[u] = val[x] + val[y];
        } else {
            int m = (l + r) / 2;
            ls[u] = join(ls[x], ls[y], l, m);
            rs[u] = join(rs[x], rs[y], m + 1, r);
            val[u] = val[ls[u]] + val[rs[u]];
        }
        return u;
    }
    int query(int L, int R, int l, int r, int rt) {
        if (!rt) return 0;
        if (L <= l && r <= R) return val[rt];
        int m = (l + r) / 2, ans = 0;
        if (L <= m) ans = query(L, R, l, m, ls[rt]);
        if (R > m) ans += query(L, R, m + 1, r, rs[rt]);
        return ans;
    }
}
using SegTrees::root;

struct sam {
    int tot, last, cnt[maxn << 1], pos[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        tot = last = 1; ms(ch[1], 0);
    }
    int insert(int c, int i) {
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        pos[cur] = i;
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                pos[nq] = pos[q];
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
    }
    void build() {
        rsort();
        for (int i = tot; i >= 2; i--) {
            int u = a[i];
            root[link[u]] = SegTrees::join(root[link[u]], root[u]);
        }
    }
    ll cal() {
        ll ans = 0;
        for (int i = 1; i <= tot; i++) {
            ans += max(0, len[i] - max(dep[pos[i]], len[link[i]]));
        }
        return ans;
    }
} f, g;

int main() {
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    f.clear();
    scanf("%s%d", s + 1, &q);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        int u = f.insert(s[i] - 'a', i);
        SegTrees::update(i, 1, n, root[u]);
    }
    f.build();
    int ql, qr, c = 0;
    while (q--) {
        c++;
        g.clear();
        scanf("%s%d%d", s + 1, &ql, &qr);
        int m = strlen(s + 1);
        int u = 1, l = 0;
        auto check = [&](int c) -> bool {
            if (!f.ch[u][c]) return false;
            int v = f.ch[u][c];
            if (ql + l <= qr && SegTrees::query(ql + l, qr, 1, n, root[v])) {
                return true;
            } else {
                return false;
            }
        };
        for (int i = 1; i <= m; i++) {
            int c = s[i] - 'a';
            g.insert(c, i);
            if (check(c)) u = f.ch[u][c], l++;
            else {
                while (u && !check(c)) {
                    if (l == 0) {
                        u = 0; break;
                    }
                    l--;
                    if (l == f.len[f.link[u]]) u = f.link[u];
                }
                if (!u) u = 1, l = 0;
                else l++, u = f.ch[u][c];
            }
            dep[i] = l;
        }
        printf("%lld\n", g.cal());
    }
    return 0;
}