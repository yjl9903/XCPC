#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace SegTrees {
    const int maxm = maxn * 60;
    int sz, root[maxn << 1], ls[maxm], rs[maxm], val[maxm];
    void update(int i, int l, int r, int& rt) {
        if (!rt) rt = ++sz, ls[rt] = rs[rt] = val[rt] = 0;
        val[rt] = 1;
        if (l == r) return ;
        int m = (l + r) / 2;
        if (i <= m) update(i, l, m, ls[rt]);
        else update(i, m + 1, r, rs[rt]);
        val[rt] = val[ls[rt]] + val[rs[rt]];
    }
    int join(int x, int y) {
        if (!x || !y) return x ^ y;
        int p = ++sz;
        val[p] = val[x] | val[y];
        ls[p] = join(ls[x], ls[y]);
        rs[p] = join(rs[x], rs[y]);
        return p;
    }
    int query(int L, int R, int l, int r, int rt) {
        if (!rt) return 0;
        if (L <= l && r <= R) return val[rt];
        int m = (l + r) / 2, ans = 0;
        if (L <= m) ans |= query(L, R, l, m, ls[rt]);
        if (R > m) ans |= query(L, R, m + 1, r, rs[rt]);
        return ans;
    }
}
using SegTrees::root;

namespace sam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        ms(ch, 0); ms(cnt, 0); tot = last = 1; 
    }
    void insert(int c) {
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1; cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; len[nq] = len[p] + 1;
                link[nq] = link[q]; link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        } 
        last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i > 1; i--) {
            int x = a[i];
            root[link[x]] = SegTrees::join(root[link[x]], root[x]);
        }
    }
}
using sam::ch;

char s[maxn];
int n, q;

int main() {
    sam::clear();
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        sam::insert(s[i] - 'a');
        SegTrees::update(i, 1, n, root[sam::last]);
    }
    sam::rsort();
    scanf("%d", &q);
    int l, r;
    while (q--) {
        scanf("%d%d%s", &l, &r, s + 1);
        int m = strlen(s + 1), u = 1, mx = m;
        vector<int> v; v.push_back(1);
        for (int i = 1; i <= m; i++) {
            int c = s[i] - 'a';
            if (ch[u][c]) v.push_back(u = ch[u][c]);
            else {
                mx = i - 1; break;
            }
        }
        assert((int)v.size() == mx + 1);
        int flag = 0;
        string ans;
        for (int i = mx; i >= 0 && !flag; i--) {
            if (l + i > r) continue;
            int st = 0, u = v[i];
            if (i < m) st = s[i + 1] - 'a' + 1;
            for (int c = st; c < 26; c++) {
                if (!ch[u][c]) continue;
                int x = ch[u][c];
                int res = SegTrees::query(l + i, r, 1, n, root[x]);
                if (res) {
                    for (int j = 1; j <= i; j++) ans += s[j];
                    ans += c + 'a'; flag = 1;
                    break;
                }
            }
        }
        if (flag) printf("%s\n", ans.c_str());
        else puts("-1");
    }
    return 0;
}