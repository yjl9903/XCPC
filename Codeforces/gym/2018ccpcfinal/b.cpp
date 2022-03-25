#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <vector>
#include <string>
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
const int inf = 1e9 + 7;
const int maxn = 200000 + 5;

int n, m, l[maxn], d[maxn];
int bel[maxn], siz[maxn], cnt[maxn][2], color[maxn], mn[maxn][2], val[maxn];
vector<int> edge[maxn];

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      edge[i].clear(); 
      color[i] = -1; cnt[i][0] = cnt[i][1] = 0;
      val[i] = -inf;
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", l + i, d + i);
    }
    int flag = 0;
    multiset<int> st;
    for (int i = 1; i <= n && !flag; i++) {
      if (color[i] != -1) continue;
      function<void(int)> dfs = [&](int u) {
        for (int v: edge[u]) {
          if (color[v] == -1) {
            bel[v] = i; 
            siz[i]++;
            color[v] = !color[u];
            if (color[v]) {
              mn[i][0] = min(mn[i][0], d[v]);
              mn[i][1] = min(mn[i][1], l[v]);
            } else {
              mn[i][0] = min(mn[i][0], l[v]);
              mn[i][1] = min(mn[i][1], d[v]);
            }
            dfs(v);
          } else if (color[v] == color[u]) {
            flag = 1; return ;
          }
        }
      };
      st.insert(-inf);
      color[i] = 0; bel[i] = i; siz[i] = 1;
      mn[i][0] = l[i]; mn[i][1] = d[i];
      dfs(i);
    }
    if (flag) {
      printf("Case %d: IMPOSSIBLE\n", ++kase);
      continue;
    }
    int ans = inf;
    vector<int> evs;
    for (int i = 1; i <= n; i++) {
      evs.push_back(i); evs.push_back(i + n);
    }
    sort(begin(evs), end(evs), [&](int a, int b) {
      int va = a <= n ? l[a] : d[a - n];
      int vb = b <= n ? l[b] : d[b - n];
      return va < vb;
    });
    for (int x: evs) {
      if (x <= n) {
        int b = bel[x], c = color[x];
        cnt[b][c]++;
        if (cnt[b][c] == siz[b]) {
          st.erase(st.find(val[b]));
          val[b] = max(val[b], mn[b][c]);
          st.insert(val[b]);
        }
        ans = min(ans, l[x] - *st.begin());
      } else {
        x -= n;
        int b = bel[x], c = color[x] ^ 1;
        cnt[b][c]++;
        if (cnt[b][c] == siz[b]) {
          st.erase(st.find(val[b]));
          val[b] = max(val[b], mn[b][c]);
          st.insert(val[b]);
        }
        ans = min(ans, d[x] - *st.begin());
      }
    }
    printf("Case %d: %d\n", ++kase, ans);
  }
  return 0;
}