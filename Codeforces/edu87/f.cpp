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
#include <random>
#include <chrono>
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

struct Query {
  static const int sz = 500;
  int l, r, id;
  bool operator < (const Query& b) const {
    if (l / sz == b.l / sz) {
      if ((l / sz) % 2) return r > b.r;
      else return r < b.r;
    }
    return l < b.l;
  }
};

int n, m, pre[maxn], suf[maxn];
ll ans[maxn];
char s[maxn];

struct Pam {
  int sz, tot, last;
  int ch[maxn][26], len[maxn], fail[maxn];
  int cnt[maxn], dep[maxn], dif[maxn], slink[maxn];
  char s[maxn];
  int node(int l) {
    sz++; ms(ch[sz], 0);
    len[sz] = l; fail[sz] = 0;
    cnt[sz] = dep[sz] = 0;
    return sz;
  }
  void clear() {
    sz = -1; last = 0;
    s[tot = 0] = '$';
    node(0); node(-1);
    fail[0] = 1;
  }
  int getfail(int x) {
    while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
    return x;
  }
  int insert(char c) {
    s[++tot] = c;
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
      int x = node(len[now] + 2);
      fail[x] = ch[getfail(fail[now])][c - 'a'];
      dep[x] = dep[fail[x]] + 1;
      ch[now][c - 'a'] = x;
 
      dif[x] = len[x] - len[fail[x]];
      if (dif[x] == dif[fail[x]]) slink[x] = slink[fail[x]];
      else slink[x] = fail[x];
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
    return last;
  }
  int get(int u, int ql) {
    if (ql > len[u]) return dep[u];
    while (true) {
      int l = len[slink[u]];
      int d = dif[u];
      if (ql >= l) {
        return (ql - l) / d + dep[slink[u]];
      }
      u = slink[u];
    }
    return 0;
  }
} f, g;

int main() {
  f.clear(); g.clear();
  scanf("%d%d%s", &n, &m, s + 1);
  for (int i = 1; i <= n; i++) pre[i] = f.insert(s[i]);
  for (int i = n; i >= 1; i--) suf[i] = g.insert(s[i]);
  vector<Query> que;
  for (int i = 1, l, r; i <= m; i++) {
    scanf("%d%d", &l, &r);
    que.push_back({ l, r, i });
  }
  sort(begin(que), end(que));
  auto getR = [&](int l, int r) {
    int u = pre[r];
    return f.get(u, r - l + 1);
  };
  auto getL = [&](int l, int r) {
    int u = suf[l];
    return g.get(u, r - l + 1);
  };
  ll tot = 0;
  for (int i = 0, l = 1, r = 0; i < m; i++) {
    while (r < que[i].r) tot += getR(l, ++r);
    while (l > que[i].l) tot += getL(--l, r);
    while (l < que[i].l) tot -= getL(l++, r);
    while (r > que[i].r) tot -= getR(l, r--);
    ans[que[i].id] = tot;
  }
  for (int i = 1; i <= m; i++) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}