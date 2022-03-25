#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int N = 2e4 + 10;
int n;
vector<int> g[N];
const int S = 17;
int fa[N][S+1], deep[N], h[N], b[N][2], dfn[N], bdfn[N];
void dfs(int x) {
    deep[x] ++;
    for (int i = 0; fa[fa[x][i]][i]; i ++) fa[x][i + 1] = fa[fa[x][i]][i];
    for (auto u:g[x])
        if (u != fa[x][0]) {
            fa[u][0] = x;
            deep[u] = deep[x];
            dfs(u);
            if (b[u][1] + 1 > b[x][1])
                b[x][1] = b[u][1] + 1, b[x][0] = u;
        }
}
int up(int x, int y){
    for (int i = S; i >= 0; i --)
        if (y >= (1 << i))
            y -= (1 << i), x = fa[x][i];
    return x;
}
int getlca(int x, int y) {
    if (deep[x] < deep[y])
        swap(x, y);
    x = up(x, deep[x] - deep[y]);
    for (int i = S; i >= 0; i --)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return x != y ? fa[x][0] : x;
}
 
struct dinic {
    int s, t;
    long long flow;
    struct edge {
        int to, rev;
        long long val;
        edge(int _to = 0, long long _val = 0, int _rev = 0)
        {
            to = _to;
            val = _val;
            rev = _rev;
        }
    };
    vector<vector<edge>> e;
    vector<int> d;
    vector<int> cur;
    void init(int _n, int _s, int _t) {
        d = vector<int>(_n + 1, 0);
        cur = vector<int>(_n + 1, 0);
        e = vector<vector<edge> >(_n + 1, vector<edge>(0));
        s = _s;
        t = _t;
        flow = 0;
    }
    void add_edge(int x, int y, long long w) {
        //printf("%d %d %lld\n", x, y, w);
        e[x].push_back(edge(y, w, e[y].size()));
        e[y].push_back(edge(x, 0, e[x].size() - 1));
 
    }
    bool bfs() {
        fill(d.begin(), d.end(), -1);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < e[x].size(); i++) {
                int y = e[x][i].to;
                if (d[y] == -1 && e[x][i].val) {
                    q.push(y);
                    d[y] = d[x] + 1;
                }
            }
        }
        if (d[t] == -1)
            return 0;
        else
            return 1;
    }
    long long dfs(int x, long long low)
    {
        if (x == t || low == 0)
            return low;
        long long totflow = 0;
        for (int &i = cur[x]; i < e[x].size(); i++) {
            int y = e[x][i].to;
            int rev = e[x][i].rev;
            if (d[y] == d[x] + 1 && e[x][i].val)
            {
                long long a = dfs(y, min(low, e[x][i].val));
                e[x][i].val -= a;
                e[y][rev].val += a;
                low -= a;
                totflow += a;
                if (low == 0)
                    return totflow;
            }
        }
        if (low != 0)
            d[x] = -1;
        return totflow;
    }
    long long solve() {
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0);
            flow += dfs(s, 1e9);
        }
        return flow;
    }
}T, tmp;
void dfs1(int x) {
    static int tot = 0;
    bdfn[dfn[x] = ++tot] = x;
    T.add_edge(x, dfn[x] + n, 1);
    if (b[x][0]) {
        h[b[x][0]] = h[x];
        dfs1(b[x][0]);
        T.add_edge(dfn[x] + n, dfn[b[x][0]] + n, n);
    }
    for (auto u:g[x])
        if (u != fa[x][0] && u != b[x][0])
            h[u] = u, dfs1(u);
}
vector<int> q[N];
vector<int> e[N];
int sz[N];
int bz[N], TAG;
void search(int l, int r, int s ,int ll, int rr, int w){
    if (r < ll|| rr < l) return;
    if (ll <= l && r <= rr) {
        T.add_edge(s+n+n, n * 6 + w + 1, 1);
        return;
    }
    search(l, (l + r) / 2, s+ s, ll, rr, w);
    search((l + r) / 2 + 1, r, s+ s +1, ll, rr, w);
}
void dfs2(int x, int v, int Fa) {
    sz[x] = (bz[x] == TAG);
    for (auto u:e[x]) {
        dfs2(u, v, x);
        sz[x] += sz[u];
    }
    if (1ll * sz[x] * v <= n) {
        int w = sz[x] * v;
        if (!Fa) {
            while (x) {
                T.add_edge(dfn[x] + n, n * 6 + w + 1, 1);
                x = fa[h[x]][0];
            }
        } else {
            while (1) {
                if (dfn[h[x]] <= dfn[Fa]) {
                    search(1, n, 1, dfn[Fa] + 1, dfn[x], w);
                    break;
                } else {
                    T.add_edge(dfn[x] + n, n * 6 + w + 1, 1);
                    x = fa[h[x]][0];
                }
            }
        }
    }
    e[x].clear();
}
void build(const vector<int>&a, int v) {
    vector<int> d;
    ++TAG;
    for (auto x:a) {
        if (d.empty()){
            d.push_back(x);
        } else {
            if (getlca(d[d.size() - 1], x) != d[d.size() - 1]) {
                int last = d[d.size() - 1];
                d.pop_back();
                while (!d.empty() && getlca(d[d.size() - 1], x) != d[d.size() - 1]) {
                    e[d[d.size() - 1]].push_back(last);
                    last = d[d.size() - 1];
                    d.pop_back();
                }
                if (d.empty() || getlca(last, x) != d[d.size() - 1] ) {
                    int u = getlca(last, x);
                    e[u].push_back(last);
                    d.push_back(u);
                } else {
                    e[d[d.size() - 1]].push_back(last);
                }
            }
            d.push_back(x);
        }
        bz[x] = TAG;
    }
    for (int i = 0;i + 1 < d.size(); i ++)
        e[d[i]].push_back(d[i + 1]);
    dfs2(d[0], v, 0);
}
void build(int l, int r, int s) {
    if (l == r) {
        T.add_edge(bdfn[l], s + 2 * n, n);
        return;
    }
    T.add_edge(s + s + 2 * n, s + 2 * n, n);
    T.add_edge(s + s + 1 + 2 * n, s + 2 * n, n);
    build(l,(l + r)/ 2, s + s);
    build((l + r) / 2 + 1, r, s + s + 1);
}
int main() {
    scanf("%d", &n);
    T.init(n * 8 + 10, n * 8 + 1, n * 8 + 2);
    for (int i = 1; i <= n; i++)
        T.add_edge(T.s, i, 1), T.add_edge(i, n * 6 + 1, 1);
    T.add_edge(n * 6 + 1, T.t, 1);
    for (int i = 2; i <= n;i ++) {
        int x;
        scanf("%d", &x);
        g[x].push_back(i);
    }
    for (int i = 1; i <= n; i ++) {
        int x;
        scanf("%d", &x);
        q[x].push_back(i);
    }
    dfs(1);
    h[1] = 1;
    dfs1(1);
    build(1, n, 1);
    for (int i = 1; i <= n; i ++)
        if (q[i].size()) {
            sort(q[i].begin(), q[i].end(), [](int x, int y) {return dfn[x] < dfn[y];});
            build(q[i], i);
        }
    int l = 0, r = n, mid, s = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        tmp = T;
        for (int i = l + 1; i <= mid; i ++)
            T.add_edge(i + n * 6 + 1, T.t, 1);
        if (T.solve() == mid + 1) {
            s = max(s, mid), l = mid + 1;
            T.add_edge(l + n * 6 + 1, T.t, 1);
        } else
            r = mid - 1, T = tmp;
    }
    printf("%d\n", s + 1);
    return 0;
}