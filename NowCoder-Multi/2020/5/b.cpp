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
#include <map>
#include <set>
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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = ~0u >> 1;
const int maxn = 200000 + 5;

namespace Trie {
  const int B = 31;
  int sz = 1, ch[maxn * B][2], val[maxn * B], ed[maxn * B];
  void clear() {
    sz = 1;
  }
  void insert(int x, int i, int v = 1) {
    int u = 1;
    for (int i = B - 1; i >= 0; i--) {
      int c = x >> i & 1;
      if (!ch[u][c]) {
        ch[u][c] = ++sz;
        ms(ch[sz], 0); val[sz] = 0;
      }
      u = ch[u][c];
      val[u] += v;
    }
    if (v > 0) {
      ed[u] = i;
    }
  }
  int qmin(int x) {
    int u = 1;
    for (int i = B - 1; i >= 0; i--) {
      int c = (x >> i & 1);
      if (ch[u][c] && val[ch[u][c]]) {
        u = ch[u][c];
      } else {
        u = ch[u][c ^ 1];
      }
    }
    return ed[u];
  }
}

int n, a[maxn];
vector<PII> edge[maxn];

int pre[maxn], siz[maxn], last[maxn], nxt[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return false;
  if (siz[x] > siz[y]) swap(x, y);
  pre[x] = y; siz[y] += siz[x];
  return true;
}

void dfs(int u, int f) {
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    a[v] = a[u] ^ x.second;
    dfs(v, u);
  }
}

int main() {
  Trie::clear();
  scanf("%d", &n);
  for (int i = 2, u, v, w; i <= n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    u++; v++;
    edge[u].emplace_back(v, w);
    edge[v].emplace_back(u, w);
  }
  dfs(1, 0);
  set<int> st;
  for (int i = 1; i <= n; i++) {
    // scanf("%d", a + i);
    // Trie::insert(a[i], i);
    st.insert(a[i]);
    pre[i] = i;
    siz[i] = 1;
  }
  n = 0;
  for (int x: st) {
    a[++n] = x;
    Trie::insert(x, n);
  }
  ll ans = 0;
  while (true) {
    for (int i = 1; i <= n; i++) last[i] = 0;
    for (int i = 1; i <= n; i++) {
      nxt[i] = last[find(i)];
      last[find(i)] = i;
    }
    vector<PII> egs;
    for (int i = 1; i <= n; i++) {
      if (i != find(i)) continue;
      int x = last[i];
      while (x) {
        Trie::insert(a[x], 0, -1);
        x = nxt[x];
      }
      x = last[i];
      int mn = inf, u, v;
      while (x) {
        int y = Trie::qmin(a[x]);
        if (y && (a[x] ^ a[y]) < mn) {
          mn = a[x] ^ a[y];
          u = x; v = y;
        }
        x = nxt[x];
      }
      if (mn != inf) {
        egs.push_back({ u, v });
      }
      x = last[i];
      while (x) {
        Trie::insert(a[x], x);
        x = nxt[x];
      }
    }
    if (egs.empty()) break;
    for (auto& e: egs) {
      int x = e.first, y = e.second;
      if (join(x, y)) {
        ans += a[x] ^ a[y];
      }
    }
  }
  cout << ans << endl;
  return 0;
}