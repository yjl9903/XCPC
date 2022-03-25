#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 100050;
typedef std::vector<int> VI;

namespace Tree {
VI C[N];
int n, pre[N], nxt[N * 2], to[N * 2], cnt;
int siz[N], wson[N], ans1[N], ans2[N], root[N];
int sumAns;

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

void dfs0(int x, int f) {
  root[x] = f ? root[f] : x;
  siz[x] = C[x].size();
  wson[x] = 0;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) {
      dfs0(to[i], x);
      siz[x] += siz[to[i]];
      if (siz[to[i]] > siz[wson[x]]) wson[x] = to[i];
    }
}

struct SomeDS {
  int A[N], num[N], maxv;

  inline void add1(int x) { --num[A[x]]; ++num[++A[x]]; maxv += num[maxv + 1] > 0; }
  inline void minus1(int x) { --num[A[x]]; ++num[--A[x]]; maxv -= num[maxv] == 0; }
} D;

void forall(int x, int f, void (SomeDS::*fun)(int)) {
  for (VI::iterator i = C[x].begin(); i != C[x].end(); ++i)
    (D.*fun)(*i);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) forall(to[i], x, fun);
}

void dfs1(int x, int f, bool keep) {
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && to[i] != wson[x])
      dfs1(to[i], x, false);
  if (wson[x]) dfs1(wson[x], x, true);
  for (VI::iterator i = C[x].begin(); i != C[x].end(); ++i)
    D.add1(*i);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && to[i] != wson[x])
      forall(to[i], x, &SomeDS::add1);
  ans1[x] = D.maxv;
  if (!keep)
    forall(x, f, &SomeDS::minus1);
}

void dfs2(int x, int f, bool keep) {
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && to[i] != wson[x])
      dfs2(to[i], x, false);
  if (wson[x]) dfs2(wson[x], x, true);
  for (VI::iterator i = C[x].begin(); i != C[x].end(); ++i)
    D.minus1(*i);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && to[i] != wson[x])
      forall(to[i], x, &SomeDS::minus1);
  ans2[x] = D.maxv;
  if (!keep)
    forall(x, f, &SomeDS::add1);
}

void Init(int nn) {
  n = nn;
  for (int i = 1; i <= n; ++i) {
    pre[i] = -1;
    C[i].clear();
    root[i] = 0;
  }
  cnt = 0;
}

void Solve() {
  sumAns = 0;
  for (int i = 1; i <= n; ++i)
    if (!root[i]) {
      dfs0(i, 0);
      dfs1(i, 0, true);
      dfs2(i, 0, true);
      sumAns += ans1[i];
    }
}

inline int getAns(int a, int b) {
  if (a == b) return sumAns;
  if (siz[a] < siz[b]) return sumAns - ans1[root[a]] + ans1[a] + ans2[a];
  else                 return sumAns - ans1[root[b]] + ans1[b] + ans2[b];
}

};

namespace Graph {
int n, pre[N], nxt[N * 2], to[N * 2], cnt;
int color[N], dfn[N], bcc[N], cnt2, cnt3;
int stack[N], ans[N], top;

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

void Init(int nn) {
  n = nn;
  for (int i = 1; i <= n; ++i) pre[i] = -1, dfn[i] = 0;
  cnt = cnt2 = cnt3 = top = 0;
}

int dfs(int x, int f) {
  stack[top++] = x;
  int lowx = dfn[x] = ++cnt2;
  for (int i = pre[x]; ~i; i = nxt[i]) if ((i ^ 1) != f) {
    if (!dfn[to[i]]) lowx = std::min(lowx, dfs(to[i], i));
    else lowx = std::min(lowx, dfn[to[i]]);
  }
  if (lowx == dfn[x]) {
    bcc[x] = ++cnt3;
    while (stack[--top] != x) bcc[stack[top]] = cnt3;
  }
  return lowx;
}

void Solve() {
  for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i, -1);
  Tree::Init(cnt3);
  for (int i = 1; i <= n; ++i)
    Tree::C[bcc[i]].push_back(color[i]);
  for (int i = 0; i < cnt; i += 2) {
    int x = to[i], y = to[i ^ 1];
    if (bcc[x] != bcc[y]) Tree::addEdge(bcc[x], bcc[y]);
  }
  Tree::Solve();
  for (int i = 0; i < cnt; i += 2)
    ans[i >> 1] = Tree::getAns(bcc[to[i]], bcc[to[i ^ 1]]);
}

};

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    Graph::Init(n);
    for (int i = 1; i <= n; ++i) scanf("%d", &Graph::color[i]);
    for (int i = 0; i < m; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      Graph::addEdge(x, y);
    }
    Graph::Solve();
    for (int i = 0; i < m; ++i)
      printf("%d%c", Graph::ans[i], " \n"[i == m - 1]);
  }
}
