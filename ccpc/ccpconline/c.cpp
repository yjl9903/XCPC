#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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

int n, q, pos[maxn];
char s[maxn];

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
    int join(int x, int y, int l, int r) {
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
    int query(int k, int l, int r, int rt) {
        if (l == r) return l;
        int m = (l + r) / 2;
        int lsum = val[rt] - val[rs[rt]];
        if (k <= lsum) return query(k, l, m, ls[rt]);
        else return query(k - lsum, m + 1, r, rs[rt]);
    }
}
using SegTrees::root;

int fa[maxn << 1][21];
namespace sam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        ms(ch, 0); 
        ms(cnt, 0); 
        ms(root, 0);
        tot = last = 1; 
    }
    int insert(int c) {
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
        return last = cur;
    }
    struct Edge {
        int to, nxt;
    } e[maxn << 1];
    int ecnt, head[maxn << 1];
    void adde(int u, int v) {
        e[++ecnt] = { v, head[u] };
        head[u] = ecnt;
    }
    void dfs(int u, int f) {
        fa[u][0] = f;
        for (int i = 1; i < 21; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (v == f) continue;
            dfs(v, u);
            root[u] = SegTrees::join(root[u], root[v], 1, n);
        }
    }
    void build() {
        ecnt = 0;
        for (int i = 0; i <= tot; i++) head[i] = 0;
        for (int i = 2; i <= tot; i++) adde(link[i], i);
        dfs(1, 0);
    }
}

int get(int u, int l) {
    for (int i = 20; i >= 0; i--) {
        if (!fa[u][i]) continue;
        int v = fa[u][i];
        if (sam::len[v] >= l) u = v;
    }
    return u;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        sam::clear(); SegTrees::tot = 0;
        scanf("%d%d%s", &n, &q, s + 1);
        for (int i = 1; i <= n; i++) {
            pos[i] = sam::insert(s[i] - 'a');
            SegTrees::update(i, 1, n, root[pos[i]]);
        }
        sam::build();
        int l, r, k;
        while (q--) {
            scanf("%d%d%d", &l, &r, &k);
            int u = get(pos[r], r - l + 1);
            if (k > SegTrees::val[root[u]]) puts("-1");
            else {
                int ed = SegTrees::query(k, 1, n, root[u]);
                printf("%d\n", ed - r + l);
            }
        }
    }
    return 0;
}