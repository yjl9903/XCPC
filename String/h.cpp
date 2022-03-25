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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n;
char s[50];

namespace acam {
  static const int maxp = 300000 + 5;
  static const int S = 26;
  int sz, ch[maxp][S], fa[maxp], fail[maxp];
  int match[maxp], val[maxp];
  int node() {
    ms(ch[++sz], 0); fail[sz] = 0; val[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int i) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int c = s[i] - 'a'; // !
      if (!ch[u][c]) ch[u][c] = node();
      fa[ch[u][c]] = u;
      u = ch[u][c];
    }
    val[u]++; match[i] = u;
    return u;
  }
  vector<int> edge[maxp];
  int siz[maxp];
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
      edge[i].clear(); siz[i] = 0;
    }
    for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    function<void(int)> dfs = [&](int u) {
      siz[u] = 1;
      for (int v: edge[u]) dfs(v), siz[u] += siz[v];
    };
    dfs(1);
  }
  ll solve() {
    ll ans = 1ll * (sz - 1) * (sz - 1);
    for (int i = 2; i <= sz; i++) {
      if (fail[i] <= 1) continue;
      int x = i, y = fail[i];
      while (y > 1) y = fa[y], x = fa[x];
      ans -= siz[x] - 1;
    }
    return ans;
  }
}

int main() {
  while (scanf("%d", &n) == 1 && n) {
    acam::clear();
    for (int i = 1; i <= n; i++) {
      scanf("%s", s);
      acam::insert(s, i);
    }
    acam::build();
    printf("%lld\n", acam::solve());
  }
  return 0;
}