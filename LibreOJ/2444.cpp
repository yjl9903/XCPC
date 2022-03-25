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
const int maxn = 100000 + 5;
const int maxp = 500000 + 5;

int b[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) b[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += b[i];
    return r;
}

int sz, ch[maxp][26], fail[maxp], ch2[maxp][26];
int siz[maxp], fa[maxp], match[maxn];
int node() {
    ms(ch[++sz], 0); fail[sz] = 0; siz[sz] = 0;
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
    siz[u]++;
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
}
int query(char* s) {
    int ans = 0;
    for (int i = 0, u = 1; s[i]; i++) {
        u = ch[u][s[i] - 'a'];
        int p = u;
        while (p > 1 && siz[p] != -1) {
            ans += siz[p];
            siz[p] = -1;
            p = fail[p];
        }
    }
    return ans;
}

int n, q, cnt, ans[maxn];
char s[maxn];
vector<int> edge[maxp];
vector<PII> que[maxp];

int tin[maxp], tout[maxp], tot;
void dfs(int u) {
    tin[u] = ++tot;
    for (int v: edge[u]) dfs(v);
    tout[u] = tot;
}

void solve(int u) {
    if (u > 1) update(tin[u], 1);
    if (!que[u].empty()) {
        for (auto& x: que[u]) {
            int v = match[x.first];
            dbg(v, tout[v], tin[v]);
            ans[x.second] = query(tout[v]) - query(tin[v] - 1);
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!ch2[u][i]) continue;
        solve(ch2[u][i]);
    }
    if (u > 1) update(tin[u], -1);
}

int main() {
    clear();
    scanf("%s%d", s, &q);
    n = strlen(s);
    for (int u = 1, i = 0; i < n; i++) {
        if (s[i] == 'P') {
            match[++cnt] = u;
        } else if (s[i] == 'B') {
            u = fa[u];
        } else {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node(), fa[ch[u][v]] = u;
            u = ch[u][v];
        }
    }
    memcpy(ch2, ch, sizeof ch);
    build();
    for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    dfs(1);
    for (int i = 1, x, y; i <= q; i++) {
        scanf("%d%d", &x, &y);
        y = match[y];
        que[y].push_back({x, i});
    }
    solve(1);
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}