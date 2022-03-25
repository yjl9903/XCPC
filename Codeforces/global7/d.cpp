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
const int maxn = 1000000 + 5;

char s[maxn];
int n;

struct pam {
  int sz, tot, last;
  int ch[maxn][26], len[maxn], fail[maxn];
  int dif[maxn], slink[maxn];;
  char s[maxn];
  int node(int l) {
    sz++; ms(ch[sz], 0);
    len[sz] = l; fail[sz] = 0;
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
      ch[now][c - 'a'] = x;

      dif[x] = len[x] - len[fail[x]];
      if (dif[x] == dif[fail[x]]) slink[x] = slink[fail[x]];
      else slink[x] = fail[x];
    }
    last = ch[now][c - 'a'];
    return last;
  }
  int get(int u, int ql) {
    if (ql > len[u]) return len[u];
    while (true) {
      int l = len[slink[u]];
      int d = dif[u];
      if (ql >= l) {
        return ((ql - l) / d) * d + l;
      }
      u = slink[u];
    }
    return 0;
  }
} f, g;

int pos1[maxn], pos2[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);

    int ans = 1, plen = 1, slen = 0;

    f.clear(); g.clear();
    for (int i = n; i >= 1; i--) {
      int u = f.insert(s[i]);
      pos1[i] = u;
      if (i == 1) {
        ans = f.len[u];
        plen = ans;
        slen = 0;
      }
    }
    for (int i = 1; i <= n; i++) {
      int u = g.insert(s[i]);
      pos2[i] = u;
      if (i == n) {
        if (g.len[u] > ans) {
          ans = g.len[u];
          plen = 0;
          slen = ans;
        }
      }
    }

    for (int i = 1; i + i <= n; i++) {
      if (s[i] == s[n - i + 1]) {
        if (n == i + i) {
          ans = n;
          plen = n;
          slen = 0;
          break;
        }

        int tot = f.get(pos1[i + 1], n - i - i);
        if (i + i + tot > ans) {
          ans = i + i + tot;
          plen = i + tot;
          slen = i;
        }

        tot = g.get(pos2[n - i], n - i - i);
        if (i + i + tot > ans) {
          ans = i + i + tot;
          plen = i;
          slen = i + tot;
        }
      } else {
        break;
      }
    }
    for (int i = 1; i <= plen; i++) {
      putchar(s[i]);
    }
    for (int i = n - slen + 1; i <= n; i++) {
      putchar(s[i]);
    }
    puts("");
  }
  return 0;
}