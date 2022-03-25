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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

inline void add(int& x, ll y) {
  x += y % mod;
  if (x >= mod) x -= mod;
}

namespace suffixTree {
  ll ans;
  int n, lcnt, lfront, sz, now, rem, s[maxn];
  int ch[maxn << 1][27], link[maxn << 1], len[maxn << 1], start[maxn << 1];
  int fa[maxn << 1], ed[maxn];
  bool isLeaf(int u) {
    for (int i = 0; i < 26; i++) 
      if (ch[u][i]) return true;
    return false;
  }
  void clear() {
    ans = 0;
    len[0] = inf;
    now = sz = 1; n = rem = 0;
    lcnt = lfront = 0;
  }
  int node(int st, int le) {
    link[++sz] = 1; ms(ch[sz], 0);
    start[sz] = st; len[sz] = le;
    fa[sz] = 0;
    if (le == inf) {
      ed[++lcnt] = sz;
    }
    return sz;
  }
  void insert(int c) {
    s[++n] = c; rem++;
    for (int last = 1; rem; ) {
      while (rem > len[ch[now][s[n - rem + 1]]]) {
        now = ch[now][s[n - rem + 1]];
        rem -= len[now];
      }
      int& v = ch[now][s[n - rem + 1]], x = s[start[v] + rem - 1];
      if (!v || x == c) {
        link[last] = now; last = now;
        if (!v) {
          v = node(n, inf);
          fa[v] = now;
        } else {
          break;
        }
      } else {
        int u = node(start[v], rem - 1);
        ch[u][x] = v;
        ch[u][c] = node(n, inf);
        fa[ch[u][x]] = u;
        fa[ch[u][c]] = u;
        start[v] += rem - 1; len[v] -= rem - 1;
        link[last] = v = u; last = u;
      }
      if (now == 1) rem--;
      else now = link[now];
    }
    ans += lcnt - lfront;
  }
  void popFront() {
    while (rem > len[ch[now][s[n - rem + 1]]]) {
      now = ch[now][s[n - rem + 1]];
      rem -= len[now];
    }
    int u = ed[++lfront];
    while (isLeaf(u) && u != now) {
      ch[fa[u]][s[start[u]]] = 0;
      ans -= min(n - start[u] + 1, len[u]);
      u = fa[u];
    }
    if (isLeaf(u) && u == now) {
      int l = min(len[u], n - start[u] + 1);
      ans -= l - rem;
      start[u] = n - rem;
      len[u] = inf;
      ed[++lcnt] = u;
      link[u] = 0;
      if (now == 1) rem--;
      else now = link[now];
    }
  }
}

int main() {
  suffixTree::clear();
  int q, ans = 0; scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    char op[2]; scanf("%s", op);
    if (op[0] == '+') {
      scanf("%s", op);
      suffixTree::insert(op[0] - 'a');
    } else if (op[0] == '-') {
      suffixTree::popFront();
    }
    add(ans, suffixTree::ans);
  }
  printf("%d\n", ans);
  return 0;
}