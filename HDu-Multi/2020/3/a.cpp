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

struct AP {
  int st, dif, cnt;
  AP(int a, int b, int c) {
    st = a;
    dif = c ? b : 0;
    cnt = c;
  }
};

namespace pam {
  int sz, tot, last;
  int ch[maxn][26], len[maxn], fail[maxn];
  int cnt[maxn], dep[maxn], dif[maxn], top[maxn];
  char s[maxn];
  int node(int l) {
    sz++; ms(ch[sz], 0);
    len[sz] = l; fail[sz] = 0;
    cnt[sz] = dep[sz] = 0;
    dif[sz] = top[sz] = 0;
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
      if (dif[x] == dif[fail[x]] && len[fail[x]] >= 1) {
        top[x] = top[fail[x]];
      } else {
        top[x] = x;
      }
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
    return last;
  }

  vector<AP> get(int u, int ql) {
    // dbg(u, ql);
    vector<AP> ans;
    while (len[u] > 0) {
      int f = top[u];
      if (ql >= len[f]) {
        if (ql >= len[u]) {
          ans.emplace_back(len[u], dif[u], (len[u] - len[f]) / dif[u]);
        } else {
          ans.emplace_back(ql, dif[u], (ql - len[f]) / dif[u]);
        }
        // dbg(ans.back().st, ans.back().dif, ans.back().cnt);
      }
      u = fail[f];
    }
    return ans;
  }
}

int n, q, node[maxn];
char s[maxn];

int solve(vector<AP>& v1, vector<AP>& v2) {
  int i = 0, j = 0;
  v1.emplace_back(0, 0, 0);
  v2.emplace_back(0, 0, 0);
  while (i + 1 < v1.size() && j + 1 < v2.size()) {
    // dbg(v1[i].st, v1[i].dif, v1[i].dif);
    // dbg(v2[j].st, v2[j].dif, v2[j].dif);
    if (v1[i].st != v2[j].st) {
      return v1[i].st < v2[j].st ? -1 : 1;
    }
    if (v1[i].dif == v2[j].dif) {
      if (v1[i].cnt == v2[j].cnt) {
        i++;
        j++;
      } else if (v1[i].cnt < v2[j].cnt) {
        int F = v1[i + 1].st;
        int G = v2[j].st - (v1[i].cnt + 1) * v2[j].dif;
        if (F != G) {
          return F < G ? -1 : 1;
        }
        v2[j].st = G;
        v2[j].cnt -= v1[i].cnt + 1;
        i++;
      } else {
        int F = v1[i].st - (v2[j].cnt + 1) * v1[i].dif;
        int G = v2[j + 1].st;
        if (F != G) {
          return F < G ? -1 : 1;
        }
        v1[i].st = F;
        v1[i].cnt -= v2[j].cnt + 1;
        j++;
      }
    } else {
      int F = v1[i].cnt ? v1[i].st - v1[i].dif : v1[i + 1].st;
      int G = v2[j].cnt ? v2[j].st - v2[j].dif : v2[j + 1].st;
      if (F != G) {
        return F < G ? -1 : 1;
      }
      if (v1[i].cnt) {
        v1[i].cnt--;
        v1[i].st -= v1[i].dif;
      } else {
        i++;
      }
      if (v2[j].cnt) {
        v2[j].cnt--;
        v2[j].st -= v2[j].dif;
      } else {
        j++;
      }
    }
  }
  if (i + 1 < v1.size()) {
    return 1;
  }
  if (j + 1 < v2.size()) {
    return -1;
  }
  return 0;
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
        auto v1 = pam::get(node[b], b - a + 1);
        auto v2 = pam::get(node[d], d - c + 1);
        int r = solve(v1, v2);
        if (r == -1) puts("sjfnb");
        else if (r == 0) puts("draw");
        else puts("cslnb");
      }
    }
  }
  return 0;
}