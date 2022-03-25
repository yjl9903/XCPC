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
#include <queue>
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
const ll inf = 1ll << 60;
const int maxn = 400000 + 5;
const int S = 14;

namespace acam {
  static const int maxp = 100000 + 5;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp];
  ll val[maxp];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int x) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - Base; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    val[u] += x;
    return u;
  }
  vector<int> edge[maxp];
  void dfs(int u) {
    for (int v: edge[u]) {
      val[v] += val[u];
      dfs(v);
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
    for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    dfs(1);
  }
}

struct State {
  int pre, nxt;
  ll val;
};

int n, k, c[maxn];
char s[maxn];
vector<pair<int,ll> > sts[maxn], nst[maxn];

int main() {
  acam::clear();
  scanf("%d", &k);
  for (int i = 1; i <= k; i++) {
    scanf("%s%d", s, c + i);
    acam::insert(s, c[i]);
  }
  acam::build();
  scanf("%s",s + 1);
  n = strlen(s + 1);
  sts[1].push_back({0, 0ll});
  vector<State> tot = { { 1, 1, 0 } };
  for (int i = 1; i <= n; i++) {
    if (s[i] == '?') {
      for (int i = 1; i <= acam::sz; i++) {
        nst[i].clear();
      }
      map<int, pair<int,ll> > mp;
      // dbg(i);
      for (auto& x: tot) {
        // dbg(x.pre, x.nxt, x.val);
        mp[x.pre] = make_pair(x.nxt, x.val);
      }
      for (int i = 1; i <= acam::sz; i++) {
        for (auto& x: sts[i]) {
          nst[mp[i].first].push_back({ x.first, mp[i].second + x.second });
          // dbg(mp[i].first, x.first, mp[i].second + x.second);
        }
      }
      swap(sts, nst);
      for (int i = 1; i <= acam::sz; i++) {
        nst[i].clear();
      }
      map<pair<int,int>,ll> g;
      for (int i = 1; i <= acam::sz; i++) {
        for (auto& x: sts[i]) {
          for (int c = 0; c < S; c++) {
            if (x.first >> c & 1) continue;
            int v = acam::ch[i][c];
            ll val = acam::val[v] + x.second;
            PII tot = { v, x.first | (1 << c) };
            if (g.count(tot)) {
              g[tot] = max(g[tot], val);
            } else {
              g[tot] = val;
            }
          }
        }
      }
      for (auto& x: g) {
        nst[x.first.first].push_back({ x.first.second, x.second });
      }
      swap(sts, nst);
      tot.clear();
      for (int i = 1; i <= acam::sz; i++) {
        if (!sts[i].empty()) {
          tot.push_back({ i, i, 0 });
        }
      }
    } else {
      int ch = s[i] - 'a';
      vector<State> nx;
      for (auto x: tot) {
        int v = acam::ch[x.nxt][ch];
        ll val = x.val + acam::val[v];
        nx.push_back({ x.pre, v, val });
      }
      tot = nx;
    }
  }
  ll ans = -inf;
  map<int, pair<int,ll> > mp;
  for (auto& x: tot) {
    mp[x.pre] = make_pair(x.nxt, x.val);
  }
  for (int i = 1; i <= acam::sz; i++) {
    for (auto& x: sts[i]) {
      // dbg(i, x.first, mp[i].second + x.second);
      ans = max(ans, mp[i].second + x.second);
    }
  }
  cout << ans << endl;
  return 0;
}