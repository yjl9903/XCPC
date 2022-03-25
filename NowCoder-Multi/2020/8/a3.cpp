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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

struct LCT {
    int fa[maxn], ch[maxn][2], rev[maxn], s[maxn];
    int nroot(int x) {return ch[fa[x]][0] == x || ch[fa[x]][1] == x;}
    int get(int x) {return ch[fa[x]][1] == x;}
    void pushup(int x) {  }
    void pushrev(int x) {
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void pushdown(int x) {
        if (!rev[x]) return;
        if (ch[x][0]) pushrev(ch[x][0]);
        if (ch[x][1]) pushrev(ch[x][1]);
        rev[x] = 0;
    }
    void rot(int x) {
        int old = fa[x], oldf = fa[old], k = get(x), w = ch[x][k ^ 1];
        if (nroot(old)) ch[oldf][ch[oldf][1] == old] = x;
        ch[x][k ^ 1] = old; ch[old][k] = w;
        if (w) fa[w] = old;
        fa[old] = x; fa[x] = oldf;
        pushup(old);
    }
    int st[maxn];
    void splay(int x) {
        int y = x, t = 0;
        st[++t] = y;
        while (nroot(y)) st[++t] = fa[y], y = fa[y];
        while (t) pushdown(st[t--]);
        while (nroot(x)) {
            y = fa[x];
            if (nroot(y)) rot(get(x) == get(y) ? y : x);
            rot(x);
        }
        pushup(x);
    }
    void access(int x) {
        for (int y = 0; x; y = x, x = fa[x])
            splay(x), ch[x][1] = y, pushup(x);
    }
    void make(int x) {
        access(x); splay(x); pushrev(x);
    }
    int findroot(int x) {
        access(x); splay(x); // findroot 把待检查的元素转上去了
        while (ch[x][0]) pushdown(x), x = ch[x][0];
        // splay(x); // ?
        return x;
    }
    void split(int x, int y) {
        make(x); access(y); splay(y);
    }
    int link(int x, int y) {
        make(x);
        if (findroot(y) == x) return 0;
        fa[x] = y;
        return 1;
    }
    int cut(int x, int y) {
        // split(x, y); fa[x] = ch[y][0] = 0; pushup(y);
        make(x);
        if (findroot(y) != x || fa[x] != y || ch[x][1]) return 0;
        // if (findroot(y) != x || size[y] > 2) return 0;
        fa[x] = ch[y][0] = 0;
        pushup(y);
        return 1;
    }
}f;

int n, m, q, fan, cnt[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &q);
  int ans = n + m;
  set<PII> st;
  for (int i = 1; i <= n; i++) {
    int k, x; scanf("%d", &k);
    while (k--) {
      scanf("%d", &x);
      ans -= f.link(i, x + n);
      st.insert(i, x);
      if (cnt[x] == 0) fan++;
      cnt[x]++;
    }
  }
  for (int i = 1, x, y; i <= q; i++) {
    scanf("%d%d", &x, &y);
    auto e = make_pair(y, x);
    if (st.count(e)) {
      f.cut(y, x + n);
      ans++;
      st.erase(e);
    } else {
      f.link()
      st.insert(e);
    }
  }
  return 0;
}