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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int B = 500;

int n, m, q, T;
bool isB[maxn];
int a[maxn], ans[maxn], ok[maxn], last[maxn];

vector<int> edge[maxn], bg[maxn];
multiset<int> neib[maxn];

vector<int> pref[maxn], dfn[maxn];

void bf() {
  for (int i = 1; i <= n; i++) {
    if (!a[i]) continue;
    bool flag = true;
    for (int v: edge[i]) {
      flag &= a[i] > a[v];
    }
    ans[i] += flag;
  }
}

void solve(int u, int delta) {
  if (!isB[u]) {
    bool flag = true;
    int ed = T;
    for (int v: edge[u]) {
      flag &= a[u] > a[v];
      if (!isB[v]) {
        if (ok[v] && a[u] >= a[v]) {
          ok[v] = false;
          ans[v] += T - last[v];
          last[v] = 0;
        }
      } else {
        // u cancel v
        neib[v].erase(neib[v].find(a[u] - delta));
        neib[v].insert(a[u]);
        if (ok[v] && a[u] >= a[v]) {
          ok[v] = false;
          ans[v] += T - last[v];
          last[v] = 0;
        }
        // v cancel u: tag
        if (ok[u] && a[v] >= a[u]) {
          int rk = lower_bound(pref[v].begin(), pref[v].end(), a[u] - delta) - pref[v].begin();
          assert(rk >= 0 && rk < pref[v].size());
          ed = min(ed, dfn[v][rk]);
        }
      }
    }
    if (!ok[u] && flag) {
      ok[u] = true;
      last[u] = T;
    } else if (ok[u] && !flag) {
      ok[u] = false;
      ans[u] += ed - last[u];
      last[u] = 0;
    }
  } else {
    bool flag = a[u] > *neib[u].rbegin();
    int ed = T;
    for (int v: bg[u]) {
      assert(isB[v]);
      // u cancel v
      neib[v].erase(neib[v].find(a[u] - delta));
      neib[v].insert(a[u]);
      if (ok[v] && a[u] >= a[v]) {
        ok[v] = false;
        ans[v] += T - last[v];
        last[v] = 0;
      }
      // v cancel u: tag
      if (ok[u] && a[v] >= a[u]) {
        int rk = lower_bound(pref[v].begin(), pref[v].end(), a[u] - delta) - pref[v].begin();
        assert(rk >= 0 && rk < pref[v].size());
        ed = min(ed, dfn[v][rk]);
      }
    }
    if (!ok[u] && flag) {
      ok[u] = true;
      last[u] = T;
    } else if (ok[u] && !flag) {
      ok[u] = false;
      ans[u] += ed - last[u];
      last[u] = 0;
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    isB[i] = edge[i].size() > B;
  }
  for (int i = 1; i <= n; i++) {
    if (isB[i]) {
      dfn[i].push_back(0);
      pref[i].push_back(0);
      for (int v: edge[i]) {
        neib[i].insert(0);
        if (isB[v]) {
          bg[i].push_back(v);
        }
      }
    }
  }
  for (T = 1; T <= q; T++) {
    int k, x;
    scanf("%d%d", &k, &x);
    bf();
    a[k] += x;
    if (isB[k]) {
      pref[k].push_back(pref[k].back() + x);
      dfn[k].push_back(T);
    }
    // solve(k, x);
  }
  for (int i = 1; i <= n; i++) {
    if (ok[i]) {
      int ed = q;
      ans[i] += ed - last[i];
    }
    printf("%d\n", ans[i]);
  }
  return 0;
}