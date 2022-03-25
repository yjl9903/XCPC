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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
  
int cnt[maxn << 2], len[maxn << 2];
void upd(int rt, int l, int r) {
  if (cnt[rt]) len[rt] = r - l + 1;
  else if (l < r) len[rt] = len[rt << 1] + len[rt << 1 | 1];
  else len[rt] = 0;
}
void update(int L, int R, int x, int l = 0, int r = 2e5, int rt = 1) {
  if (L <= l && r <= R) {
    cnt[rt] += x; upd(rt, l, r);
    return ;
  }
  int m = (l + r) / 2;
  if (L <= m) update(L, R, x, lson);
  if (R > m) update(L, R, x, rson);
  upd(rt, l, r);
}
  
int m, n, k, t, a[maxn];
vector<PII> bag[maxn];
  
int main() {
  scanf("%d%d%d%d", &m, &n, &k, &t);
  for (int i = 1; i <= m; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + m + 1, greater<int>());
  for (int i = 1, l, r, x; i <= k; i++) {
    scanf("%d%d%d", &l, &r, &x);
    bag[x].push_back({l, r});
  }
  int p = maxn - 1, ans = 0;
  for (int i = 1; i <= m; i++) {
    while (p > a[i]) {
      for (auto& x: bag[p]) {
        update(x.first, x.second, 1);
      }
      p--;
    }
    int sum = 1 + n + 2 * len[1];
    if (sum <= t) ans = i;
    else break;
  }
  printf("%d\n", ans);
  return 0;
}