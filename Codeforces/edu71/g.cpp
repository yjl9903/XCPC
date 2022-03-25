#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

struct BIT {
    int a[maxn];
    void update(int i, int x) {
        for (; i < maxn; i += i & -i) a[i] += x;
    }
    int query(int i) {
        int r = 0;
        for (; i; i -= i & -i) r += a[i];
        return r;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} g;

namespace acam {
    static const int maxp = 500000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    int node() {
        ms(ch[++sz], 0); fail[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    int insert(char* s) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        return u;
    }
    vector<int> edge[maxp];
    int tin[maxp], tout[maxp];
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
        int tot = 0;
        function<void(int)> dfs = [&](int u) {
            tin[u] = ++tot;
            for (int v: edge[u]) {
                dfs(v);
            }
            tout[u] = tot;
        };
        dfs(1);
    }
}
using acam::ch;
using acam::tin;
using acam::tout;

int n, q, ans[maxn];
int trie[maxn][26], sz = 1, pos[maxn];
char s[maxn];

vector<PII> que[maxn];
void dfs(int u, int x) {
    g.update(tin[x], 1);
    for (auto q: que[u]) {
        int v = q.first, id = q.second;
        ans[id] = g.query(tin[v], tout[v]);
    }
    for (int c = 0; c < 26; c++) {
        if (!trie[u][c]) continue;
        int v = trie[u][c];
        dfs(v, acam::ch[x][c]);
    }
    g.update(tin[x], -1);
}

int main() {
    acam::clear();
    scanf("%d", &n);
    for (int i = 1, op, fa; i <= n; i++) {
        scanf("%d", &op);
        char s[5];
        if (op == 1) {
            scanf("%s", s);
            fa = 1;
        } else {
            scanf("%d%s", &fa, s);
            fa = pos[fa];
        }
        int c = s[0] - 'a';
        if (!trie[fa][c]) trie[fa][c] = ++sz;
        pos[i] = trie[fa][c];
    }
    scanf("%d", &q);
    for (int i = 1, t; i <= q; i++) {
        scanf("%d%s", &t, s);
        int u = acam::insert(s);
        que[pos[t]].push_back({u, i});
    }
    acam::build();
    dfs(1, 1);
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}