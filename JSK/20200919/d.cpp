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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, K, w[maxn], a[maxn], f[maxn];
int tot, dfn[maxn], dep[maxn], fa[20][maxn];
vector<int> edge[maxn], bag[maxn];

void getdep(int u, int f) {
  fa[0][u] = f;
  for (int i = 1; i < 20; i++) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
  }
  dfn[u] = ++tot;
  dep[u] = dep[f] + 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    getdep(v, u);
  }
}

int qlca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  int tmp = dep[x] - dep[y];
  for (int i = 0; tmp; i++, tmp >>= 1)
    if (tmp & 1) x = fa[i][x];
  if (x == y) return x;
  for (int i = 19; i >= 0; i--) {
    if (fa[i][x] != fa[i][y]) {
      x = fa[i][x]; y = fa[i][y];
    }
  }
  return fa[0][x];
}

namespace VT {
  int stk[maxn], top;
  void build(vector<int>& vec) {
    sort(vec.begin(), vec.end(), [&](int a, int b) { return dfn[a] < dfn[b]; });
    stk[top = 1] = 1; edge[1].clear();
    for (int x: vec) {
      if (x == 1) continue;
      int g = qlca(stk[top], x);
      if (g != stk[top]) {
        while (dfn[g] < dfn[stk[top - 1]]) {
          edge[stk[top - 1]].push_back(stk[top]); top--;
        }
        if (dfn[g] > dfn[stk[top - 1]]) {
          edge[g].clear();
          edge[g].push_back(stk[top]);
          stk[top] = g;
        } else {
          edge[g].push_back(stk[top]); top--;
        }
      }
      edge[x].clear(); stk[++top] = x;
    }
    for (int i = 1; i < top; i++) {
      edge[stk[i]].push_back(stk[i + 1]);
    }
  }
}

int D, siz[maxn], son[maxn];
void getsz(int u, int f) {
  siz[u] = 1;
  son[u] = 0;
  for (auto& v : edge[u]) {
    if (v == f) continue;
    getsz(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
int res, cnt[maxn], sk[maxn];
void add(int u, int f, int x) {
  // update answer
  if (dep[u] == D) {
    int tag = K ^ w[u];
    if (x == 1) {
      if (tag < maxn && cnt[tag]) res++;
      cnt[w[u]]++;
    } else if (x == -1) {
      cnt[w[u]]--;
      if (tag < maxn && cnt[tag]) res--;
    }
  }
  for (auto& v : edge[u]) {
    if (v == f || sk[v]) continue;
    add(v, u, x);
  }
}
void dfs(int u, int f, int kp) {
  a[u] = 0;
  for (auto& v : edge[u]) {
    if (v == f || v == son[u]) continue;
    dfs(v, u, 0);
    a[u] |= a[v];
  }
  if (son[u]) {
    dfs(son[u], u, 1);
    sk[son[u]] = 1;
  }
  add(u, f, 1);
  sk[son[u]] = 0;
  // answert query
  if (res > 0) {
    a[u] |= 1;
  }
  if (a[u]) {
    ::f[u]++;
  }
  if (!kp) add(u, f, -1);
}

int main() {
  scanf("%d%d", &n, &K);
  for (int i = 2, f; i <= n; i++) {
    scanf("%d", &f);
    edge[f].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", w + i);
  }
  getdep(1, 0);
  for (int i = 1; i <= n; i++) {
    bag[dep[i]].push_back(i);
    edge[i].clear();
  }
  for (int i = 2; i <= n; i++) {
    if (bag[i].empty()) continue;
    VT::build(bag[i]);
    D = i;
    res = 0;
    getsz(1, 0);
    dfs(1, 0, 0);
    // ans += cal(dfs(rt, 0), 1);
    for (int x: bag[i]) a[x] = 0;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = (ans + (i ^ (n - f[i]))) % mod;
  }
  cout << ans << endl;
  return 0;
}