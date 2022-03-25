#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

struct fastIO {
  char s[100000]; int it,len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, 100000, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  bool notend() {
    char c = get();
    while(c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;
inline int gi() {
  int r = 0; bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}

int n, nn, q;
ll sa[maxn], sb[maxn], ssb[maxn];

vector<ll> lsh;
int sz, root[maxn], ls[maxn * 21], rs[maxn * 21], cnt[maxn * 21];
ll sum[maxn * 21];
void update(int i, int pre, int l, int r, int& rt) {
  rt = ++sz; ls[rt] = ls[pre]; rs[rt] = rs[pre];
  sum[rt] = sum[pre] + lsh[i - 1];
  cnt[rt] = cnt[pre] + 1;
  if (l == r) return ;
  int m = (l + r) / 2;
  if (i <= m) update(i, ls[pre], lson);
  else update(i, rs[pre], rson);
}
ll qsum(int i, int pre, int l, int r, int rt) {
  if (l == r) return sum[rt] - sum[pre];
  int m = (l + r) / 2;
  if (i <= m) return qsum(i, ls[pre], lson) + sum[rs[rt]] - sum[rs[pre]];
  else return qsum(i, rs[pre], rson);
}
ll qcnt(int i, int pre, int l, int r, int rt) {
  if (l == r) return cnt[rt] - cnt[pre];
  int m = (l + r) / 2;
  if (i <= m) return qcnt(i, ls[pre], lson) + cnt[rs[rt]] - cnt[rs[pre]];
  else return qcnt(i, rs[pre], rson);
}

int main() {
  n = gi(); q = gi();
  for (int i = 1; i <= n; i++) sa[i] = gi();
  for (int i = 1; i <= n; i++) sb[i] = gi();
  for (int i = 1; i <= n; i++) {
    sa[i] += sa[i - 1];
    sb[i] += sb[i - 1];
    ssb[i] = sb[i] + ssb[i - 1];
    lsh.push_back(sa[i] - sb[i]);
  }
  lsh.push_back(0);
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  nn = (int)lsh.size();
  for (int i = 1; i <= n; i++) {
    int id = lower_bound(begin(lsh), end(lsh), sa[i] - sb[i]) - begin(lsh) + 1;
    update(id, root[i - 1], 1, nn, root[i]);
  }
  while (q--) {
    int l = gi(); int r = gi();
    int id = lower_bound(begin(lsh), end(lsh), sa[l - 1] - sb[l - 1]) - begin(lsh) + 1;
    ll ans = ssb[r] - ssb[l - 1];
    ans += qsum(id, root[l - 1], 1, nn, root[r]);
    ans -= sb[l - 1] * (r - l + 1);
    ans += qcnt(id, root[l - 1], 1, nn, root[r]) * (sb[l - 1] - sa[l - 1]);
    printf("%I64d\n", ans);
  }
  return 0;
}