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
#include <set>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
const int maxn = 1000000 + 5;

namespace acam {
  static const int maxp = 1000000 + 5;
  static const int S = 26;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp], val[maxp], link[maxn];
  int tot, tin[maxp], tout[maxp];
  vector<int> edge[maxp];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int id) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - Base; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    val[u] = id;
    return u;
  }
  void dfs(int u) {
    tin[u] = ++tot;
    for (int v: edge[u]) {
      link[v] = val[v] > 0 ? v : link[u];
      dfs(v);
    }
    tout[u] = tot;
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
    for (int i = 2; i <= sz; i++) {
      edge[fail[i]].push_back(i);
    }
    link[1] = -1;
    dfs(1);
  }
}

struct Bit {
  int a[maxn];
  void update(int i, int x) {
    for (; i < maxn; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
} f;

int n, pre[maxn], lnk[maxn];
char buf[maxn];

int main() {
  acam::clear();
  scanf("%d", &n);
  vector<string> allS { "" };
  for (int i = 1; i <= n; i++) {
    scanf("%s", buf);
    acam::insert(buf, i);
    allS.emplace_back(buf);
  }
  acam::build();
  int ans = 0;
  for (auto& str: allS) {
    for (int i = 0, u = 1; i < str.length(); i++) {
      u = acam::ch[u][str[i] - 'a'];
      pre[i + 1] = u;
      if (i + 1 < str.length()) {
        int p = acam::link[u];
        lnk[i + 1] = p;
      } else {
        int p = acam::link[acam::fail[u]];
        lnk[i + 1] = p;
      }
    }
    auto update = [&](int x, int y = 1) {
      if (x < 1) return ;
      f.update(acam::tin[x], y);
    };
    auto marked = [&](int x) {
      return f.query(acam::tin[x], acam::tout[x]);
    };
    vector<int> add;
    set<int> key;
    int L = str.length() + 1;
    for (int i = str.length(); i >= 1; i--) {
      int x = lnk[i];
      if (x == -1) continue;
      int match = acam::val[x];
      if (i - allS[match].length() < L) {
        L = i - allS[match].length();
        key.insert(x);
        x = acam::fail[x];
      }
      if (x != -1) add.push_back(x);
    }
    for (int x: add) update(x, 1);
    for (int x: key) ans += marked(x) == 0;
    for (int x: add) update(x, -1);
    assert(!marked(1));
  }
  printf("%d\n", ans);
  return 0;
}