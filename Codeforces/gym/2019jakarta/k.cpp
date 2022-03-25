#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct Mat {
  static const int M = 2;
  ll a[M][M];
  Mat() { ms(a, 0); }
  void clear() { ms(a, 0); }
  void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
  ll* operator [] (ll x) { return a[x]; }
  const ll* operator [] (ll x) const { return a[x]; }
  Mat operator * (const Mat& b) {
    const Mat& a = *this; Mat r;
    for (int i = 0; i < M; i++)
      for (int j = 0; j < M; j++)
        for (int k = 0; k < M; k++)
          r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % mod;
    return r;
  }
  Mat pow(ll n) const {
    Mat a = *this, r; r.eye();
    while (n > 0) {
      if (n & 1)  r = r * a;
      n >>= 1; a = a * a;
    }
    return r;
  }
  Mat operator + (const Mat& b) {
    const Mat& a = *this; Mat r;
    for (int i = 0; i < M; i++)
      for (int j = 0; j < M; j++)
        r[i][j] = (a[i][j] + b[i][j]) % mod;
    return r;
  }
  void trans() {
    swap(a[0][0], a[1][1]);
    swap(a[1][0], a[0][1]);
  }
  void print() const {
    for (int i = 0; i < M; i++) for (int j = 0; j < M; j++)
      printf("%lld%c", (*this)[i][j], " \n"[j == M - 1]);
  }
} a[maxn << 2], ans;

int n, q, tag[maxn << 2];
char s[maxn];

void pushdown(int rt) {
  if (!tag[rt]) return ;
  a[rt << 1].trans();
  tag[rt << 1] ^= 1;
  a[rt << 1 | 1].trans();
  tag[rt << 1 | 1] ^= 1;
  tag[rt] = 0;
}
void update(int L, int R, int l = 1, int r = n, int rt = 1) {
  if (L <= l && r <= R) {
    a[rt].trans();
    tag[rt] ^= 1;
    return ;
  }
  int m = (l + r) / 2; pushdown(rt);
  if (R > m) update(L, R, rson);
  if (L <= m) update(L, R, lson);
  a[rt] = a[rt << 1 | 1] * a[rt << 1];
}

void build(int l = 1, int r = n, int rt = 1) {
  if (l == r) {
    a[rt][0][0] = a[rt][1][1] = 1;
    if (s[l] == 'A') {
      a[rt][0][1] = 1;
    } else {
      a[rt][1][0] = 1;
    }
    return ;
  }
  int m = (l + r) / 2;
  build(rson); build(lson);
  a[rt] = a[rt << 1 | 1] * a[rt << 1];
}

void query(int L, int R, int l = 1, int r = n, int rt = 1) {
  if (L <= l && r <= R) {
    ans = ans * a[rt];
    return ;
  }
  int m = (l + r) / 2; pushdown(rt);
  if (R > m) query(L, R, rson);
  if (L <= m) query(L, R, lson);
}

int main() {
  scanf("%d%d%s", &n, &q, s + 1);
  build();
  for (int i = 1, op, l, r, a, b; i <= q; i++) {
    scanf("%d%d%d", &op, &l, &r);
    if (op == 1) {
      update(l, r);
    } else if (op == 2) {
      scanf("%d%d", &a, &b);
      ans.clear(); ans.eye();
      query(l, r);
      Mat s;
      s[0][0] = a;
      s[1][0] = b;
      ans = ans * s;
      printf("%I64d %I64d\n", ans[0][0], ans[1][0]);
    }
  }
  return 0;
}