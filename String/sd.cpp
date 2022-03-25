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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

inline void add(int& x, ll y) {
  x += y % mod;
  if (x >= mod) x -= mod;
}

namespace STree {
  struct Node {
    int l, r, par, fail;
    map<int,int> nxt;
    Node() {}
    Node(int l, int r, int par): l(l), r(r), par(par), fail(0) {}
    int next(int ch) {
      return nxt.count(ch) ? nxt[ch] : 0;
    }
  } e[maxn << 2];
  int s[maxn]; // 原串
  // rem: 未插入后缀长度
  // (curP, curC, curL) 当前隐式后缀的位置
  int sz, n, rem, curP, curC, curL;

  ll ans = 0; // 本质不同子串
  int que[maxn], qL = 0, qR = 0; // 叶子结点
  // [l, r)
  int node(int l, int r, int par) {
    e[++sz] = Node(l, r, par);
    return sz;
  }
  void clear() {
    sz = n = rem = 0;
    curP = node(0, 0, 0);
    e[1].fail = 1;
    curC = curL = 0;
    qL = qR = 0;
  }
  void insert(int ch) {
    s[++n] = ch; rem++;
    for (int last = 0; rem; rem--) {
      if (curL == 0) curC = n;
      int p = e[curP].next(s[curC]);
      while (p && curL >= e[p].r - e[p].l) {
        curC += e[p].r - e[p].l;
        curL -= e[p].r - e[p].l;
        curP = p;
        p = e[curP].next(s[curC]);
      }
      if (!p) {
        int u = e[curP].nxt[s[curC]] = node(n, inf, curP);
        que[++qR] = u;
        if (last) e[last].fail = curP;
        last = curP;
      } else if (s[e[p].l + curL] == ch) {
        curL++;
        if (last) e[last].fail = curP;
        break;
      } else {
        int u = node(e[p].l, e[p].l + curL, curP);
        int v = node(n, inf, u);
        que[++qR] = v;
        e[p].par = u;
        e[p].l += curL;
        e[curP].nxt[s[curC]] = u;
        e[u].nxt[s[e[p].l]] = p;
        e[u].nxt[ch] = v;
        if (last) e[last].fail = u;
        last = u;
      }
      if (curP == 1 && curL) {
        curL--; curC++;
      } else {
        curP = e[curP].fail;
      }
    }
    ans += qR - qL;
  }
}

int main() {
  STree::clear();
  int q, ans = 0; scanf("%d", &q);
  for (int i = 1, x; i <= q; i++) {
    scanf("%d", &x);
    STree::insert(x);
    printf("%lld\n", STree::ans);
  }
  return 0;
}