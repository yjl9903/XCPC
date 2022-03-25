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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, q, a[maxn], pre[maxn];
int tot, root[maxn], ls[maxn * 40], rs[maxn * 40], cnt[maxn * 40];
ll sum[maxn * 40];

void insert(int i, int x, int pre, int l, int r, int& rt) {
  rt = ++tot;
  ls[rt] = ls[pre];
  rs[rt] = rs[pre];
  cnt[rt] = cnt[pre] + 1;
  sum[rt] = sum[pre] + x;
  if (l == r) return ;
  int m = (l + r) / 2;
  if (i <= m) insert(i, x, ls[pre], lson);
  else insert(i, x, rs[pre], rson);
}

ll qsum(int i, int pre, int l, int r, int rt) {
  if (l == r) return sum[rt] - sum[pre];
  int m = (l + r) / 2;
  if (i <= m) return qsum(i, ls[pre], lson);
  else return sum[ls[rt]] - sum[ls[pre]] + qsum(i, rs[pre], rson);
}

// int qmax(int k, int pre, int l, int r, int rt) {
//   if (l > k) return -1;
//   if (cnt[rt] - cnt[pre] == 0) return -1;
//   if (l == r) return l;
//   int m = (l + r) / 2;
//   int res = qmax(k, rs[pre], rson);
//   if (res != -1) return res;
//   return qmax(k, ls[pre], lson);
// }

int main() {
  scanf("%d%d", &n, &q);
  vector<ll> lsh;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    lsh.push_back(a[i]);
    pre[i] = pre[i - 1];
    if (a[i] == 1) pre[i]++;
  }
  sort(lsh.begin(), lsh.end());
  lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
  int nn = lsh.size();
  auto gid = [&](ll x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
  };
  for (int i = 1; i <= n; i++) {
    int x = gid(a[i]);
    insert(x, a[i], root[i - 1], 1, nn, root[i]);
  }
  auto query = [&](int l, int r) {
    if (pre[r] - pre[l - 1] == 0) return 1ll;
    ll ans = 1;
    int last = 0;
    while (true) {
      int id = gid(ans + 1) - 1;
      ll nxt = qsum(id, root[l - 1], 1, nn, root[r]);
      dbg(id, ans, nxt);
      if (nxt + 1 == ans) break;
      ans = nxt + 1;
    }
    return ans;
  };
  ll ans = 0;
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    l = (l + ans) % n + 1;
    r = (r + ans) % n + 1;
    if (l > r) swap(l, r);
    // dbg(l, r);
    printf("%lld\n", ans = query(l, r));
  }
  return 0;
}