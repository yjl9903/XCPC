#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
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
const int maxr = 500 + 5;

struct acam {
  static const int maxp = 200000 + 5;
  static const int S = 26;
  int sz, ch[maxp][S], fail[maxp];
  int node() {
    ms(ch[++sz], 0); fail[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  acam() { clear(); }
  vector<int> insert(char* s) {
    int u = 1;
    vector<int> p;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - 'A';
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
      p.push_back(u);
    }
    return p;
  }
  vector<int> edge[maxp];
  int dfn[maxp], siz[maxp];
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < S; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
    for (int i = 0; i <= sz; i++) edge[i].clear();
    for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    int id = 0;
    function<void(int)> dfs = [&](int u) {
      dfn[u] = ++id; siz[u] = 1;
      for (int v: edge[u]) {
        dfs(v); siz[u] += siz[v];
      }
    };
    dfs(1);
  }
} g, rg;

int n, m, q, ans[maxn];
int rowp[maxr][maxr], colp[maxr][maxr];
char s[maxr][maxr], t[maxn];

struct Node {
  int x, y, id, sgn;
  bool operator<(const Node& b) const {
    if (x == b.x) return id < b.id;
    return x < b.x;
  }
};

int c[maxn];
void update(int i, int x) {
  for (; i < maxn; i += i & -i) c[i] += x;
}
int query(int i) {
  int r = 0;
  for (; i; i -= i & -i) r += c[i];
  return r;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
  vector<tuple<int,int,int> > allq;
  g.clear(); rg.clear();
  for (int i = 1; i <= q; i++) {
    scanf("%s", t); int m = strlen(t);
    auto a = g.insert(t);
    reverse(t, t + m);
    auto b = rg.insert(t);
    reverse(begin(b), end(b));
    for (int j = 0; j < m; j++) {
      allq.emplace_back(a[j], b[j], i);
    }
  }
  g.build(); rg.build();
  for (int i = 1; i <= n; i++) {
    int u = 1;
    for (int j = 1; j <= m; j++) {
      u = g.ch[u][s[i][j] - 'A'];
      rowp[i][j] = u;
    }
  }
  for (int j = 1; j <= m; j++) {
    int u = 1;
    for (int i = n; i >= 1; i--) {
      u = rg.ch[u][s[i][j] - 'A'];
      colp[i][j] = u;
    }
  }
  vector<Node> que;
  for (auto& x: allq) {
    int u, v, id; tie(u, v, id) = x;
    int l = g.dfn[u], r = g.dfn[u] + g.siz[u] - 1;
    int b = rg.dfn[v], t = rg.dfn[v] + rg.siz[v] - 1;
    que.push_back({l - 1, b - 1, id, 1});
    que.push_back({r, b - 1, id, -1});
    que.push_back({l - 1, t, id, -1});
    que.push_back({r, t, id, 1});
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int u = rowp[i][j], v = colp[i][j];
      que.push_back({g.dfn[u], rg.dfn[v], 0, 1});
    }
  }
  sort(begin(que), end(que));
  for (auto& x: que) {
    int id = x.id;
    if (id == 0) {
      update(x.y, 1);
    } else {
      ans[id] += x.sgn * query(x.y);
    }
  }
  for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
  return 0;
}