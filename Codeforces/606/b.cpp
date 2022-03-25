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
const int maxn = 500000 + 5;

int n, m, a, b, vis[maxn];
vector<int> edge[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      vis[i] = 0;
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }

    int suma = 0, sumb = 0;
    map<int,int> mp;
    set<int> as, bs;

    function<void(int,set<int>&)> dfs = [&](int u, set<int>& st) {
      if (vis[u]) return ;
      vis[u] = 1; 
      mp[u]++; st.insert(u);
      for (int v: edge[u]) {
        if (v == a || v == b) continue;
        dfs(v, st);
      }
    };

    dfs(a, as);
    for (int i = 1; i <= n; i++) vis[i] = 0;
    dfs(b, bs);

    for (auto& x: mp) {
      if (x.second == 2) {
        as.erase(x.first);
        bs.erase(x.first);
      }
    }
    as.erase(a);
    bs.erase(b);

    printf("%I64d\n", 1ll * (int)as.size() * (int)bs.size());
  }
  return 0;
}