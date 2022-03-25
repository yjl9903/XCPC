#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
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
const int maxn = 300000 + 5;

int n, q, pos[maxn], val[maxn];
char buffer[maxn];

namespace acam {
  static const int maxp = maxn;
  static const int S = 26;
  static const int Base = 'a';

  int sz, ch[maxp][S], fail[maxp], link[maxn];
  multiset<int> vals[maxn];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = 0;
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
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    vals[u].insert(0);
    return u;
  }
  vector<int> edge[maxp];
  void dfs(int u, int f) {
    link[u] = f;
    if (!vals[u].empty()) f = u;
    for (int v: edge[u]) {
      dfs(v, f);
    }
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
    dfs(1, -1);
  }

  void update(int u, int old, int val) {
    vals[u].erase(vals[u].find(old));
    vals[u].insert(val);
  }
  int query(int u) {
    if (vals[u].empty()) {
      return -1;
    } else {
      return *vals[u].rbegin();
    }
  }
}

int main() {
  acam::clear();
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%s", buffer);
    pos[i] = acam::insert(buffer, i);
  }
  acam::build();
  while (q--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int i, x;
      scanf("%d%d", &i, &x);
      acam::update(pos[i], val[i], x);
      val[i] = x;
    } else if (op == 2) {
      scanf("%s", buffer);
      int ans = -1;
      for (int i = 0, u = 1; buffer[i]; i++) {
        u = acam::ch[u][buffer[i] - 'a'];
        int x = u;
        while (x > 0) {
          ans = max(ans, acam::query(x));
          x = acam::link[x];
        }
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}