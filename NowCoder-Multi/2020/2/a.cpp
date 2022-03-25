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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, pos[maxn];
char s[maxn];

namespace acam {
  static const int maxp = 1000000 + 5;
  static const int S = 26;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp], fa[maxn], siz[maxp], val[maxp], dep[maxn];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = siz[sz] = 0;
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
      if (!ch[u][v]) {
        ch[u][v] = node();
        fa[ch[u][v]] = u;
      }
      u = ch[u][v];
      dep[u] = i + 1;
    }
    val[u]++;
    siz[u]++;
    return u;
  }
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
    for (int i = 2; i <= sz; i++) {
      edge[fail[i]].push_back(i);
    }
  }
  void dfs(int u) {
    for (int v: edge[u]) {
      dfs(v);
      siz[u] += siz[v];
    }
  }
}

int fail[maxn], cnt[maxn];

int main() {
  acam::clear();
  scanf("%d", &n);
  vector<string> allS;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    allS.emplace_back(s);
    pos[i] = acam::insert(s, i);
  }
  acam::build();
  acam::dfs(1);
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    string& s = allS[i - 1];
    fail[1] = 0;
    for (int i = 2; i <= (int)s.length(); i++) {
      int cur = fail[i - 1];
      while (cur > 0 && s[cur] != s[i - 1]) cur = fail[cur];
      if (s[cur] == s[i - 1]) cur++;
      fail[i] = cur;
    }
    int u = pos[i];
    dbg(i);
    for (int i = (int)s.length(); i >= 1; i--) {
      int c = acam::siz[u] - cnt[i];
      dbg(acam::siz[u], cnt[i], acam::dep[u]);
      // ans += 1ll * c * i * i;
      ans = (ans + 1ll * c * i * i % mod) % mod;
      cnt[fail[i]] += acam::siz[u];
      u = acam::fa[u];
    }
    for (int i = 0; i <= (int)s.length(); i++) {
      fail[i] = cnt[i] = 0;
    }
  }
  cout << ans << endl;
  return 0;
}