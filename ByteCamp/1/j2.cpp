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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 100000 + 5;

struct LinearBase {
  static const int maxl = 63;
  ll a[maxl + 5];
  int cnt, pos[maxl + 5];
  LinearBase() { cnt = 0; ms(a, 0); }
  void clear() { cnt = 0; ms(a, 0); }
  bool insert(ll x, int p) {
    ll tmp = x;
    for (int i = maxl - 1; i >= 0; i--) {
      if (x & (1ll << i)) {
        if (a[i]) {
          x ^= a[i];
        } else {
          a[i] = tmp; pos[i] = p; cnt++;
          return true;
        }
      }
    }
    return false;
  }
  pair<bool, vector<int> > check(ll x) {
    vector<int> ans;
    for (int i = maxl - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (a[i]) x ^= a[i], ans.push_back(pos[i]);
        else return { false, ans };
      }
    }
    return { true, ans };
  }
} lb;

struct BIT {
  int a[maxn * 2];
  void clear() {
    for (int i = 0; i < maxn  * 2; i++) a[i] = -1;
  }
  void update(int i, int x) {
    for (i++; i < maxn * 2; i += i & -i) a[i] = max(a[i], x);
  }
  int query(int i) {
    int r = -1;
    for (i++; i; i -= i & -i) r = max(r, a[i]);
    return r;
  }
} f;

struct Event {
  int x, y, id;
  bool operator <(const Event& b) const {
    if (x != b.x) return x < b.x;
    if (y != b.y) return y < b.y;
    return id > b.id;
  }
};

int n, k, base[maxn], ok[2][maxn];
bool dp[maxn][2];
PII a[maxn];

int main() {
  scanf("%d%d", &n, &k);
  vector<Event> evs;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    evs.push_back({ a[i].first, a[i].second, i });
    evs.push_back({ a[i].second, a[i].first, -i });
  }
  for (int i = 1; i <= k; i++) {
    scanf("%d", base + i);
  }
  sort(begin(evs), end(evs)); f.clear();
  for (int i = 0, j = 0; i < n + n; i = j) {
    while (j < n + n && evs[j].x == evs[i].x) {
      int x = evs[j].x, y = evs[j].y, id = evs[j].id;
      if (id > 0) {
        ok[0][id] = f.query(y - 1) + 1;
      } else if (id < 0) {
        ok[1][-id] = f.query(y - 1) + 1;
      }
      j++;
    }
    for (int p = i; p < j; p++) {
      int x = evs[p].x, y = evs[p].y, id = evs[p].id;
      if (id > 0) {
        f.update(y, ok[0][id]);
      }
    }
  }
  lb.clear();
  ll sum = 0;
  for (int i = 1; i <= k; i++) {
    int id = base[i];
    sum ^= ok[0][id];
    lb.insert(ok[0][id] ^ ok[1][id], i);
  }
  auto ans = lb.check(sum);
  if (ans.first) {
    set<int> st; for (int x: ans.second) st.insert(x);
    for (int i = 1; i <= k; i++) {
      if (st.count(i)) putchar('1');
      else putchar('0');
    }
  } else {
    puts("impossible");
  }
  return 0;
}