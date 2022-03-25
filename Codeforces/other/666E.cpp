#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef pair<ll,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 550000 + 5;
int flag = 0;
char s[maxn];
int slen, n, q, pos[maxn];

namespace SegTrees {
    const int maxm = maxn * 32;
    int tot, root[maxn << 1], ls[maxm], rs[maxm];
    PII val[maxm];
    PII cal(PII a, PII b) {
        if (a.first > b.first) return a;
        else if (a.first == b.first && a.second < b.second) return a;
        else return b;
    }
    void update(int i, int l, int r, int& rt) {
        if (!rt) rt = ++tot;
        if (l == r) {
            val[rt].first++;
            val[rt].second = i;
            return ;
        }
        int m = (l + r) / 2;
        if (i <= m) update(i, l, m, ls[rt]);
        else update(i, m + 1, r, rs[rt]);
        val[rt] = cal(val[ls[rt]], val[rs[rt]]);
    }
    int join(int x, int y, int l = 1, int r = n) {
        if (!x || !y) return x + y;
        int u = ++tot;
        if (l == r) {
            val[u].first = val[x].first + val[y].first;
            val[u].second = l;
        } else {
            int m = (l + r) / 2;
            ls[u] = join(ls[x], ls[y], l, m);
            rs[u] = join(rs[x], rs[y], m + 1, r);
            val[u] = cal(val[ls[u]], val[rs[u]]);
        }
        return u;
    }
    PII query(int L, int R, int l, int r, int rt) {
        if (!rt) return { -1, inf };
        if (L <= l && r <= R) return val[rt];
        int m = (l + r) / 2;
        if (R <= m) return query(L, R, l, m, ls[rt]);
        else if (L > m) return query(L, R, m + 1, r, rs[rt]);
        else return cal(query(L, R, l, m, ls[rt]), query(L, R, m + 1, r, rs[rt]));
    }
}
using SegTrees::root;

int fa[maxn << 1][21];
namespace sam {
    int tot, last;
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        tot = last = 1; 
    }
    int insert(int c) {
        if (ch[last][c]) {
            int p = last;
            int q = ch[p][c];
            if (len[q] == len[p] + 1) return last = q;
            int nq = ++tot;
            len[nq] = len[last] + 1;
            link[nq] = link[q];
            link[q] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            return last = nq;
        }
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        len[cur] = len[last] + 1; 
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
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
        for (int i = 2; i <= tot; i++) {
            if (link[i] > tot || link[i] < 0) for(;;);
            adde(link[i], i);
        }
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
    sam::clear();
    scanf("%s%d", s + 1, &n);
    slen = strlen(s + 1);
    for (int i = 1; i <= slen; i++) {
        pos[i] = sam::insert(s[i] - 'a');
    }
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        sam::last = 1;
        for (int j = 1; s[j]; j++) {
            int u = sam::insert(s[j] - 'a');
            SegTrees::update(i, 1, n, root[u]);
        }
    }
    sam::build();
    int l, r, pl, pr;
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d%d%d", &l, &r, &pl, &pr);
        int u = get(pos[pr], pr - pl + 1);
        dbg(u);
        PII ans = SegTrees::query(l, r, 1, n, root[u]);
        if (ans.second == inf) printf("%d 0\n", l);
        else printf("%d %lld\n", ans.second, ans.first);
    }
    return 0;
}