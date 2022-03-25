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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
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

int n;
char s[maxn], t[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  int mn[maxn << 2], mx[maxn << 2], tag[maxn << 2];
  void pushup(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
  void pushdown(int rt) {
    if (!tag[rt]) return ;
    int t = tag[rt];
    mx[rt << 1] += t;
    mn[rt << 1] += t;
    tag[rt << 1] += t;
    mx[rt << 1 | 1] += t;
    mn[rt << 1 | 1] += t;
    tag[rt << 1 | 1] += t;
    tag[rt] = 0;
  }
  void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      tag[rt] += x; mx[rt] += x; mn[rt] += x;
      return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }
  int query(int i, int l = 1, int r = n, int rt = 1) {
    if (l == r) return mx[rt];
    int m = (l + r) / 2; pushdown(rt);
    if (i <= m) return query(i, lson);
    else return query(i, rson);
  }
}

int main() {
  scanf("%d%s", &n, s + 1);
  int p = 1, len = 0;
  set<int> posr, posl;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'R') {
      p++;
    } else if (s[i] == 'L') {
      p--;
      if (p == 0) {
        p = 1;
      }
    } else if (s[i] == '(') {
      int ad = 0;
      if (t[p]) {
        if (t[p] == ')') {
          ad = 2;
          posr.erase(p);
        } else if (t[p] == '(') {

        } else {
          ad = 1;
        }
      } else {
        ad = 1;
      }
      t[p] = '(';
      posl.insert(p);
      SegT::update(p, n, ad);
    } else if (s[i] == ')') {
      int ad = 0;
      if (t[p]) {
        if (t[p] == ')') {

        } else if (t[p] == '(') {
          ad = -2;
          posl.erase(p);
        } else {
          ad = -1;
        }
      } else {
        ad = -1;
      }
      t[p] = ')';
      posr.insert(p);
      SegT::update(p, n, ad);
    } else {
      int ad = 0;
      if (t[p] == ')') {
        posr.erase(p);
        ad = 1;
      } else if (t[p] == '(') {
        posl.erase(p);
        ad = -1;
      }
      t[p] = s[i];
      SegT::update(p, n, ad);
    }

    int ans = 0;
    if (posl.empty() && posr.empty()) {
      ans = 0;
    } else if (posl.empty() || posr.empty()) {
      ans = -1;
    } else {
      int pr = *posr.rbegin();
      int pl = *posl.rbegin();
      if (pl > pr || SegT::query(pr) || SegT::mn[1] < 0) {
        ans = -1;
      } else {
        ans = SegT::mx[1];
      }
    }
    printf("%d ", ans);
  }
  return 0;
}