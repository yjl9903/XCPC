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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

struct Bit {
  int n, a[maxn];
  void clear(int _n) {
    n = _n;
    for (int i = 0; i <= n; i++) a[i] = 0;
  }
  void update(int i, int x) {
    for (; i <= n; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int L, int R) {
    if (L > R) return 0;
    return query(R) - query(L - 1);
  }
} f;

int n, P, a[maxn], b[maxn], vis[maxn];
PII ev[maxn];

int cal(int x) {
  int r = 1ll * x * P / 100;
  if (1ll * x * P % 100) r++;
  return r;
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &P);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", a + i, b + i);
      vis[i] = 0;
      ev[i + i - 1] = { a[i], i };
      ev[i + i] = { b[i], i };
      lsh.push_back(a[i]);
      lsh.push_back(b[i]);
      if (a[i] > b[i]) swap(a[i], b[i]);
    }
    sort(begin(lsh), end(lsh));
    lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
    auto gid = [&](int x) {
      return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
    };
    int nn = lsh.size();
    f.clear(nn);
    for (int i = 1; i <= n; i++) {
      f.update(gid(b[i]), 1);
    }
    sort(ev + 1, ev + 1 + n + n, [&](PII& lhs, PII& rhs) {
      if (lhs.first != rhs.first) {
        return lhs.first > rhs.first;
      } else if (lhs.second == rhs.second) {
        return true;
      } else {
        int r1 = a[lhs.second] == lhs.first;
        int r2 = a[rhs.second] == rhs.first;
        return r1 > r2;
      }
    });
    int ans = 0;
    for (int i = 1; i <= n + n; i++) {
      int val = cal(ev[i].first);
      ans = max(ans, f.query(gid(val), nn));
      int id = ev[i].second;
      // dbg(ev[i].first, val, id);
      if (vis[id]) {
        break;
      } else {
        vis[id] = true;
        f.update(gid(ev[i].first), -1);
        f.update(gid(ev[i].first ^ a[id] ^ b[id]), 1);
      }
    }
    printf("Case #%d: %d\n", ++kase, ans);
  }
  return 0;
}