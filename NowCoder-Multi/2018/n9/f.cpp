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
const int maxn = 200000 + 5;

int n, m;
char s[maxn];

namespace acam {
  static const int maxp = 200000 + 5;
  static const int S = 26;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp], val[maxp];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(const char s[]) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - Base; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    val[u] = 1;
    return u;
  }
  vector<int> edge[maxp];
  int dis[maxp];
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < S; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          val[ch[t][i]] |= val[fail[ch[t][i]]];
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
    for (int i = 1; i <= sz; i++) {
      for (int j = 0; j < S; j++) {
        if (ch[i][j]) {
          edge[ch[i][j]].push_back(i);
        }
      }
    }
    for (int i = 0; i <= sz; i++) {
      if (val[i]) {
        dis[i] = 0; q.push(i);
      } else {
        dis[i] = inf;
      }
    }
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v: edge[u]) {
        if (dis[v] > dis[u] + 1) {
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }
  }
}

int main() {
  acam::clear();
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", s); acam::insert(s);
  }
  acam::build();
  scanf("%s", s);
  printf("%d\n", acam::dis[1]);
  vector<int> stk = { 1 };
  for (int i = 0; s[i]; i++) {
    if (s[i] == '-') {
      stk.pop_back();
      if (stk.empty()) stk.push_back(1);
    } else {
      stk.push_back(acam::ch[stk.back()][s[i] - 'a']);
    }
    int ans = inf;
    printf("%d\n", acam::dis[stk.back()]);
  }
  return 0;
}