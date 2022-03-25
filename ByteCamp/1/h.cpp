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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
using ll = long long;
using PII = pair<int,int>;
using PLL = pair<ll,ll>;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

PLL operator - (PLL a, PLL b) {
  return make_pair(a.first - b.first, a.second - b.second);
}
ll cross(PLL a, PLL b) {
  return a.first * b.second - a.second * b.first;
}
ll xmult(PLL a, PLL b, PLL c) {
  // 0 -> 三点共线
  // + -> AC 在 AB 的逆时针方向
  // - -> AC 在 AB 的顺时针方向
  return cross(b - a, c - a);
}

struct Event {
  int h, le, id;
} q[maxn];

int n, a[maxn], root[maxn];
ll ans[maxn];

vector<PLL> upd[maxn << 2];
void insert(PLL x, int L, int R, int l = 1, int r = n, int rt = 1) {
  if (L <= l && r <= R) {
    upd[rt].push_back(x); return ;
  }
  int m = (l + r) / 2;
  if (L <= m) insert(x, L, R, lson);
  if (R > m) insert(x, L, R, rson);
}
void dfs(int l = 1, int r = n, int rt = 1) {
  if (l < r) {
    int m = (l + r) / 2;
    dfs(lson); dfs(rson);
  }
  if (upd[rt].empty()) return ;
  sort(begin(upd[rt]), end(upd[rt]), [](const PLL& a, const PLL& b) {
    return a.first == b.first ? a.second > b.second : a.first < b.first;
  });
  vector<PLL> q = { upd[rt][0] };
  for (int i = 1; i < (int)upd[rt].size(); i++) {
    while ((int)q.size() >= 2 && xmult(q[(int)q.size() - 2], q.back(), upd[rt][i]) > 0) {
      q.pop_back();
    }
    q.push_back(upd[rt][i]);
  }
  auto ask = [&](int x) {
    ll ans = ::ans[x - 1];
    for (int l = 0, r = (int)q.size() - 1; l <= r;) {
      int len = (r - l) / 3, m1 = l + len, m2 = r - len;
      ll s1 = 1ll * x * q[m1].first + q[m1].second;
      ll s2 = 1ll * x * q[m2].first + q[m2].second;
      if (s1 > s2) {
        r = m2 - 1;
        if (ans < s1) ans = s1;
      } else {
        l = m1 + 1;
        if (ans < s2) ans = s2;
      }
    }
    return ans;
  };
  for (int i = l; i <= r; i++) {
    ans[i] = max(ans[i], ask(i + 1));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  int ed = 0;
  for (int i = 1; i <= n; i++) {
    int pos = i;
    while (ed > 0 && q[ed].h > a[i]) {
      pos = q[ed].le;
      insert({ q[ed].h, -1ll * q[ed].h * q[ed].le }, q[ed].id, i - 1);
      ed--;
    }
    q[++ed] = { a[i], pos, i };
  }
  while (ed > 0) {
    insert({ q[ed].h, -1ll * q[ed].h * q[ed].le }, q[ed].id, n);
    ed--;
  }
  dfs();
  for (int i = 1; i <= n; i++) {
    ans[i] = max(ans[i], ans[i - 1]);
    printf("%lld\n", ans[i]);
  }
  return 0;
}