#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
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
const int maxn = 200000 + 5;
const int maxm = 2000000 + 5;

namespace ACAM {
    static const int maxp = 2000000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    int match[maxp];
    int node() {
        ms(ch[++sz], 0); fail[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    void insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        match[i] = u;
    }
    vector<int> edge[maxp];
    int tot, tin[maxp], tout[maxp];
    int siz[maxp], dep[maxp], fa[maxp], son[maxp], top[maxp];
    void dfs(int u, int f) {
        tin[u] = ++tot;
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
        tout[u] = tot;
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp); // !
        for (auto& v: edge[u]) {
            if (v == f || v == son[u]) continue; // !
            dfs(v, u, v);
        }
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
        for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
        dfs(1, 0); dfs(1, 0, 1);
    }
    int b[maxp];
    void update(int i, int x) {
        for (; i <= sz; i += i & -i) b[i] += x;
    }
    void update(char* s) {
        int u = 1;
        vector<int> v;
        for (int i = 0; s[i]; i++) {
            if (!ch[u][s[i] - 'a']) break;
            u = ch[u][s[i] - 'a'];
            v.push_back(u);
        }
        sort(v.begin(), v.end(), [&](int a, int b) {
            return tin[a] < tin[b];
        });
        int last = -1;
        for (int x: v) {
            dbg(x);
            update(tin[x], 1);
            // update(tout[x] + 1, -1);
            if (last != -1) {
                int g = qlca(last, x);
                update(tin[g], -1);
                // update(tout[g] + 1, 1);
            }
            last = x;
        }
    }
    int query(int x) {
        int ans = 0, i = tin[match[x]] - 1;
        for (; i; i -= i & -i) ans -= b[i];
        i = tout[match[x]];
        for (; i; i -= i & -i) ans += b[i];
        return ans;
    }
}

int n, q, op;
char s[maxn];

int main() {
    ACAM::clear();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        ACAM::insert(s, i);
    }
    ACAM::build();
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%s", s);
            ACAM::update(s);
        } else {
            int x; scanf("%d", &x);
            printf("%d\n", ACAM::query(x));
        }
    }
    return 0;
}