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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k, dep[maxn], fa[maxn], deg[maxn], siz[maxn];
ll ans = 0;
vector<int> edge[maxn];

void dfs(int u, int f) {
  fa[u] = f;
  siz[u] = 1;
  dep[u] = dep[f] + 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
    deg[u]++;
    siz[u] += siz[v];
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  set<PII> st;
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 0) {
      st.insert({ dep[i] - 1, i });
    }
  }
  for (int i = 1; i <= k; i++) {
    auto it = st.end(); it--;
    ans += it->first;
    int u = it->second;
    deg[fa[u]]--;
    if (u && deg[fa[u]] == 0) {
      st.insert({ dep[fa[u]] - siz[fa[u]], fa[u] });
    }
    st.erase(it);
  }
  cout << ans << endl;
  return 0;
}