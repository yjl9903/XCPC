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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

namespace acam {
  static const int maxp = 500000 + 5;
  static const int S = 26;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp], val[maxp], len[maxp];
  int node(int l = 0) {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = 0;
    len[sz] = l;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int i) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - Base; // !
      if (!ch[u][v]) ch[u][v] = node(i + 1);
      u = ch[u][v];
    }
    val[u]++;
    return u;
  }
  int ed[maxp];
  vector<int> edge[maxp];
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
    for (int i = 1; i <= sz; i++) {
      edge[i].clear(); ed[i] = -1;
    }
    for (int i = 2; i <= sz; i++) {
      edge[fail[i]].push_back(i);
    }
    function<void(int)> dfs = [&](int u) {
      if (val[u] && ed[u] == -1) {
        ed[u] = len[u];
      }
      for (int v: edge[u]) {
        if (ed[u] != -1) {
          ed[v] = ed[u];
        }
        dfs(v);
      }
    };
    dfs(1);
  }
}

int n, dp[maxn];
char s[maxn], t[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    acam::clear();
    scanf("%s%d", s + 1, &n);
    for (int i = 1; i <= n; i++) {
      scanf("%s", t);
      acam::insert(t, i);
    }
    acam::build();
    int m = strlen(s + 1);
    for (int i = 0; i <= m; i++) dp[i] = 0;
    for (int i = 1, u = 1; i <= m; i++) {
      u = acam::ch[u][s[i] - 'a'];
      if (acam::ed[u] != -1) {
        dp[i] = dp[i - acam::ed[u]] + 1;
      }
      dp[i] = max(dp[i], dp[i - 1]);
    }
    printf("%d\n", dp[m]);
  }
  return 0;
}