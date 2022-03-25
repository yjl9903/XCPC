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
  char s[maxn]; // 原串
  // rem: 未插入后缀长度
  // (curP, curC, curL) 当前隐式后缀的位置
  int sz, n, rem, curP, curC, curL;

  struct Node {
    int st, len, par, fail;
    map<char,int> nxt;
    Node() {}
    Node(int st, int len, int par): st(st), len(len), par(par), fail(0) {}
    int next(char ch) {
      return nxt.count(ch) ? nxt[ch] : 0;
    }
    int length() {
      return min(len, n - st);
    }
  } e[maxn << 1];

  ll ans = 0; // 本质不同子串
  int que[maxn << 1], qL = 0, qR = 0; // 叶子结点

  // [l, r)
  int node(int st, int len, int par) {
    e[++sz] = Node(st, len, par);
    return sz;
  }
  void clear() {
    n = rem = 0; sz = 0;
    curP = node(0, 0, 0);
    e[1].fail = 1;
    curC = curL = 0;
    qL = qR = 0;
  }
  void insert(char ch) {
    s[n++] = ch; rem++;
    for (int last = 1; rem; rem--) {
      if (curL == 0) curC = n - 1;
      int p = e[curP].next(s[curC]);
      while (p && curL >= e[p].len) {
        curC += e[p].len;
        curL -= e[p].len;
        curP = p;
        p = e[p].next(s[curC]);
      }
      if (p == 0) {
        assert(curL == 0);
        int u = e[curP].nxt[s[curC]] = node(n - 1, inf, curP);
        que[++qR] = u;
        e[last].fail = curP;
        last = curP;
      } else if (s[e[p].st + curL] == ch) {
        curL++;
        e[last].fail = curP;
        break;
      } else {
        int u = node(e[p].st, curL, curP);
        int v = node(n - 1, inf, u);
        que[++qR] = v;
        e[p].par = u;
        e[p].st += curL;
        e[p].len -= curL;
        e[curP].nxt[s[curC]] = u;
        e[u].nxt[s[e[p].st]] = p;
        e[u].nxt[ch] = v;
        e[last].fail = u;
        last = u;
      }
      if (curP == 1) {
        if (curL) {
          curL--; curC++;
        }
      } else {
        curP = e[curP].fail;
      }
    }
    ans += qR - qL;
    dbg(curP, curL, curC);
  }
  void popFront() {
    if (curL) {
      int p = e[curP].next(s[curC]);
      while (p && curL >= e[p].len) {
        curC += e[p].len;
        curL -= e[p].len;
        curP = p;
        p = e[p].next(s[curC]);
      }
    }
    int u = que[++qL];
    while (u != curP && e[u].nxt.empty()) {
      e[e[u].par].nxt.erase(s[e[u].st]);
      ans -= e[u].length();
      u = e[u].par;
    }
    if (rem && u == curP) {
      if (curL == 0 && e[u].nxt.empty()) {
        ans -= e[u].length();
        if (e[u].len < inf) {
          e[u].st = n - e[u].len;
          e[u].len = inf;
        }
        ans += e[u].length();
        que[++qR] = u;
      } else if (curC < n && !e[u].next(s[curC])) {
        int v = node(n - curL, inf, u);
        e[u].nxt[s[curC]] = v;
        ans += e[v].length();
        que[++qR] = v;
      } else {
        return ;
      }
      if (curP == 1) {
        if (curL) {
          curL--; curC++;
        }
      } else {
        curP = e[curP].fail;
      }
      rem--;
    }
  }
}

int main() {
  STree::clear();
  int q, ans = 0; scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    char op[3]; scanf("%s", op);
    if (op[0] == '+') {
      scanf("%s", op);
      STree::insert(op[0]);
    } else if (op[0] == '-') {
      STree::popFront();
    }
    dbg(STree::ans);
    add(ans, STree::ans);
  }
  printf("%d\n", ans);
  return 0;
}