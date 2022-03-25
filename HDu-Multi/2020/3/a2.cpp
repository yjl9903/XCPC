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
const int maxn = 100000 + 5;

namespace pam {
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
}
using pam::len;
using pam::fail;
using pam::slink;
using pam::dif;

int n, q, node[maxn];
char s[maxn];

vector<tuple<int,int,int> > get(int l, int r) {
  int qlen = r - l + 1;
  int u = node[r];
  vector<tuple<int,int,int> > vec;
  while (u) {
    int l = len[slink[u]];
    int d = dif[u];
    if (qlen >= l) {
      if (len[u] > qlen) {
        int beg = ((qlen - l) / d) * d + l;
        if (beg == l) {
          vec.emplace_back(beg, l, dif[slink[u]]);
        } else {
          vec.emplace_back(beg, l, d);
        }
      } else {
        vec.emplace_back(len[u], l, d);
      }
    }
    u = slink[u];
  }
  return vec;
}

char t[maxn];
int fa[maxn];
vector<int> bf(int l, int r) {
  for (int i = l; i <= r; i++) {
    t[i - l + 1] = s[i];
  }
  fa[1] = 0;
  for (int i = 2; i <= r - l + 1; i ++) {
    int cur = fa[i - 1];
    while (cur && t[cur + 1] != t[i]) cur = fa[cur];
    if (t[cur + 1] == t[i]) cur++;
    fa[i] = cur;
  }
  vector<int> vec;
  int u = r - l + 1;
  while (u) {
    vec.push_back(u);
    u = fa[u];
  }
  // for (int x: vec) {
  //   dbg(x);
  // }
  return vec;
}

vector<int> bf2(int l, int r) {
  vector<int> v;
  int u = node[r];
  while (u) {
    if (pam::len[u] <= r - l + 1) {
      v.push_back(pam::len[u]);
    }
    u = pam::fail[u];
  }
  return v;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s%d", &n, s + 1, &q);
    pam::clear();
    for (int i = 1; i <= n; i++) {
      node[i] = pam::insert(s[i]);
    }
    while (q--) {
      int a, b, c, d;
      scanf("%d%d%d%d", &a, &b, &c, &d);
      if (b - a + 1 != d - c + 1) {
        puts(b - a + 1 < d - c + 1 ? "sjfnb" : "cslnb");
      } else {
        auto v1 = bf2(a, b);
        auto v2 = bf2(c, d);
        if (v1 != v2) {
          puts(v1 < v2 ? "sjfnb" : "cslnb");
        } else {
          puts("draw");
        }
      }
    }
  }
  return 0;
}