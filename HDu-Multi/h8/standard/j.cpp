#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <=(n); i++)
#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#else
# define _debug(...) ((void)0)
#endif
#define prev aehfuhf

const int MAXN = 200007;
int n, m, tot;
int h[200005];
int st[MAXN][32-__builtin_clz(MAXN)];
int dp[200005];
int sel[200005], prev[200005], c[200005];

void init_st() {
  int l = 31 - __builtin_clz(n);
  rep (i, n) st[i][0] = h[i];
  rep (j, l) rep (i, 1+n-(1<<j))
    st[i][j+1] = max(st[i][j], st[i+(1<<j)][j]);
}

int rmq(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  return max(st[l][k], st[r-(1<<k)+1][k]);
}

int first_gt_after(int pos, int val) {
  int l = pos + 1, r = n, mid; 
  while (r > l) {
    mid = (l + r) / 2;
    if (rmq(pos+1, mid) <= val) l = mid + 1;
    else r = mid;
  }
  return l;
}

void prep() {
  int cnt = 1;
  dp[n] = 0;
  for (int i = n - 1; i >= 0; i--) {
    int pos = first_gt_after(i, h[i]);
    dp[i] = dp[pos] + 1;
  }
  sel[0] = 1; prev[0] = -1; c[0] = 1;
  int last = 0, lasth = h[0];
  for (int i = 1; i < n; i++) {
    prev[i] = last;
    if (h[i] > lasth) {
      sel[i] = 1;
      last = i;
      lasth = h[i];
      cnt++;
    } else sel[i] = 0;
    c[i] = cnt;
  }
  tot = cnt;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    rep (i, n) scanf("%d", &h[i]);
    init_st();
    prep();
//    rep (i, n) printf("dp[%d]=%d\n", i, dp[i]);
    rep (i, m) { 
      int p, q; scanf("%d%d", &p, &q); p--;
      if (sel[p]) {
        if (p == 0) {
            _debug("kase 0");
          int ans = 1;
          int pos = first_gt_after(p, q);
          ans += dp[pos];
          printf("%d\n", ans);
        } else {
          if (q <= h[prev[p]]) {
            _debug("kase 1");
            int cl = c[prev[p]];
            int pos = first_gt_after(p, h[prev[p]]);
            cl += dp[pos];
            printf("%d\n", cl);
          } else {
            _debug("kase 2");
            int cl = c[p];
            int pos = first_gt_after(p, q);
            cl += dp[pos];
            printf("%d\n", cl);
          }
        }
      } else {
        if (q <= h[prev[p]]) {
            _debug("kase 3");
          printf("%d\n", tot);
        } else {
            _debug("kase 4");
          int cl = c[prev[p]] + 1;
          int pos = first_gt_after(p, q);
          cl += dp[pos];
          printf("%d\n", cl);
        }
      } 
    }
  }
  return 0;
}
