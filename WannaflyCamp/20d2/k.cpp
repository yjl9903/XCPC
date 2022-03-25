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
#include <queue>
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
const ll inf = 1ll << 61;
const int maxn = 500000 + 5;

int n, p[maxn];
ll dp[maxn];
char s[maxn];

namespace acam {
  static const int maxp = 500000 + 5;
  static const int S = 26;
  int sz, ch[maxp][S], fail[maxp];
  int val[maxp], len[maxp];
  int node() {
    ms(ch[++sz], 0); fail[sz] = 0;
    val[sz] = 1e9; len[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int i) {
    int u = 1, l = 0;
    for (int i = 0; s[i]; i++, l++) {
      int v = s[i] - 'a'; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    len[u] = l; val[u] = min(val[u], p[i]);
    return u;
  }
  int link[maxp];
  vector<int> edge[maxp];
  void dfs(int u, int last) {
    link[u] = last;
    if (len[u]) last = u;
    for (int v: edge[u]) dfs(v, last);
  }
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
    for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    dfs(1, 0);
  }
}

int main() {
  acam::clear();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s%d", s, p + i);
    acam::insert(s, i);
  }
  acam::build();
  scanf("%s", s + 1);
  int m = strlen(s + 1);
  for (int i = 1; i <= m; i++) dp[i] = inf;
  for (int i = 1, u = 1; i <= m; i++) {
    u = acam::ch[u][s[i] - 'a'];
    int x = u;
    do {
      if (acam::len[x]) {
        dp[i] = min(dp[i], dp[i - acam::len[x]] + acam::val[x]);
      }
      x = acam::link[x];
      // dbg(u, x);
    } while(x > 1);
  }
  if (dp[m] == inf) puts("-1");
  else printf("%I64d\n", dp[m]);
  return 0;
}