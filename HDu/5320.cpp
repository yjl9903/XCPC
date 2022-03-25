#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int add(int x, int y) {
  x += y; return x >= mod ? x - mod : x;
}
int mul(int x, int y) {
  return 1ll * x * y % mod;
}

int n, g[18][maxn];
int qgcd(int l, int r) {
  int k = __lg(r - l + 1);
  return __gcd(g[k][l], g[k][r - (1 << k) + 1]);
}

struct Node {
  int x, i, l, r;
  bool operator< (const Node& b) const {
    if (x == b.x) return i < b.i;
    return x < b.x;
  }
} vec[maxn * 30];

struct Info {
  int val, sum;
  void clear() { val = sum = 0; }
  Info(int a = 0, int b = 0): val(a), sum(b) {}
  Info operator+(const Info& b) {
    if (val < b.val) return Info(b.val, b.sum);
    else if (val > b.val) return Info(val, sum);
    else return Info(val, add(sum, b.sum));
  }
  Info operator+=(const Info& b) {
    return *this = *this + b;
  }
} t[maxn * 4], tag[maxn * 4];
int time, pos[maxn * 4];

void build(int l = 1, int r = n, int rt = 1) {
  pos[rt] = -1; t[rt].clear(); tag[rt].clear();
  if (l == r) return ;
  int m = (l + r) / 2;
  build(lson); build(rson);
}
void clear(int rt) {
  if (pos[rt] < time) {
    pos[rt] = time;
    t[rt].clear(); tag[rt].clear();
  }
}
void upd(int rt, Info x, int len) {
  clear(rt);
  t[rt] += Info(x.val, mul(x.sum, len));
  tag[rt] += x;
}
void pushdown(int rt, int ln, int rn) {
  if (!tag[rt].val) return ;
  upd(rt << 1, tag[rt], ln);
  upd(rt << 1 | 1, tag[rt], rn);
  tag[rt].clear();
}
void pushup(int rt) {
  clear(rt << 1); clear(rt << 1 | 1);
  t[rt] = t[rt << 1] + t[rt << 1 | 1];
}
Info query(int L, int R, int l = 1, int r = n, int rt = 1) {
  clear(rt);
  if (L <= l && r <= R) return t[rt];
  int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
  Info ans;
  if (R <= m) ans = query(L, R, lson);
  else if (L > m) ans = query(L, R, rson);
  else ans = query(L, R, lson) + query(L, R, rson);
  return ans;
}
void update(int L, int R, const Info& x, int l = 1, int r = n, int rt = 1) {
  clear(rt);
  if (L <= l && r <= R) {
    upd(rt, x, r - l + 1); return ;
  }
  int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
  if (L <= m) update(L, R, x, lson);
  if (R > m) update(L, R, x, rson);
  pushup(rt);
}

int main() {
  while (scanf("%d", &n) == 1) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", &g[0][i]);
    }
    for (int j = 1; j < 18; j++) {
      for (int i = 1; i + (1 << j) <= n + 1; i++) {
        g[j][i] = __gcd(g[j - 1][i], g[j - 1][i + (1 << (j - 1))]);
      }
    }
    build();
    int sz = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) {
        int l = j, r = n, ans = j, g = qgcd(i, j);
        while (l <= r) {
          int m = (l + r) / 2;
          if (qgcd(i, m) == g) {
            ans = m; l = m + 1;
          } else {
            r = m - 1;
          }
        }
        vec[sz++] = (Node){ g, i, j, ans };
        j = ans;
      }
    }
    sort(vec, vec + sz);
    Info ans;
    for (int i = 0, j; i < sz; i = j) {
      j = i; time = vec[i].x;
      while (j < sz && vec[j].x == vec[i].x) {
        Info r;
        if (vec[j].i > 1) {
          r = query(1, vec[j].i - 1);
        }
        if (r.val == 0) {
          r.val = r.sum = 1;
        } else {
          r.val++;
        }
        update(vec[j].l, vec[j].r, r);
        r.sum = mul(r.sum, vec[j].r - vec[j].l + 1);
        ans += r; j++;
      }
    }
    printf("%d %d\n", ans.val, ans.sum);
  }
  return 0;
}