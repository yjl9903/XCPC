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

struct BIT {
  int a[maxn * 2];
  void update(int i, int x) {
    for (i++; i < maxn * 2; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (i++; i; i -= i & -i) r += a[i];
    return r;
  }
} f, h;

struct Event {
  int x, y, id;
  bool operator <(const Event& b) const {
    if (x != b.x) return x < b.x;
    if (y != b.y) return y < b.y;
    return id > b.id;
  }
};

int n, k, base[maxn], ok[3][maxn];
bool dp[maxn][2];
PII a[maxn];

int main() {
  scanf("%d%d", &n, &k);
  vector<Event> evs;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    evs.push_back({ a[i].first, a[i].second, i });
  }
  for (int i = 1; i <= k; i++) {
    scanf("%d", base + i);
    int x = a[base[i]].first, y = a[base[i]].second;
    evs.push_back({ x, y, -i });
    evs.push_back({ y, x, -i - k });
  }
  sort(begin(evs), end(evs));
  for (int i = 0, j = 0; i < n + k + k; i = j) {
    while (j < n + k + k && evs[j].x == evs[i].x) {
      int x = evs[j].x, y = evs[j].y, id = evs[j].id;
      int tSum = f.query(y - 1), rSum = h.query(y - 1);
      if (rSum == 0 || tSum < rSum) {
        if (id > 0) {
          ok[0][id] = true;
        } else if (id < 0) {
          id = -id;
          if (id <= k) ok[1][id] = true;
          else ok[2][id - k] = true;
        }
      }
      j++;
    }
    for (int p = i; p < j; p++) {
      int x = evs[p].x, y = evs[p].y, id = evs[p].id;
      if (id > 0) {
        h.update(y, 1);
        if (ok[0][id]) {
          f.update(y, 1);
        }
      }
    }
  }
  int cnt = 0;
  for (int i = 1; i <= k; i++) {
    if (ok[1][i] && ok[2][i]) cnt++;
  }
  string ans;
  for (int i = 1; i <= k; i++) {
    dbg(i, ok[1][i], ok[2][i]);
    if (ok[1][i] && ok[2][i]) {
      ans += "0";
    } else if (ok[1][i] || ok[2][i]) {
      if (cnt % 2 == 0) {
        cnt++;
        if (ok[1][i]) ans += "0";
        else ans += "1";
      } else {
        if (ok[1][i]) ans += "1";
        else ans += "0";
      }
    } else {
      ans += "0";
    }
  }
  if (cnt % 2) puts(ans.c_str());
  else puts("impossible");
  // for (int i = 1; i <= n; i++) {
  //   dbg(i, ok[0][i]);
  // }
  // for (int i = 1; i <= k; i++) {
  //   dbg(i, ok[1][i], ok[2][i]);
  // }
  // dp[0][0] = true;
  // for (int i = 1; i <= k; i++) {
  //   bool tot[2] = { false, false };
  //   if (ok[1][i] || ok[2][i]) {
  //     tot[0] = true;
  //   }
  //   if (!ok[1][i] || !ok[2][i]) {
  //     tot[1] = true;
  //   }
  //   if (dp[i - 1][0] && tot[0]) dp[i][0] = true;
  //   if (dp[i - 1][0] && tot[1]) dp[i][1] = true;
  //   if (dp[i - 1][1] && tot[0]) dp[i][1] = true;
  //   if (dp[i - 1][1] && tot[1]) dp[i][0] = true;
  //   dbg(i, dp[i][0], dp[i][1]);
  // }
  // string ans;
  // if (ans.length() == k) {
  //   puts(ans.c_str());
  // } else {
  //   puts("impossible");
  // }
  return 0;
}