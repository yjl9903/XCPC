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
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct Node {
  int first, second, id;

  bool operator< (const Node& rhs) const {
    if (second != rhs.second) {
      return second < rhs.second;
    } else {
      return first < rhs.first;
    }
  }

  ll dis(const Node& rhs) const {
    int dx = first - rhs.first;
    int dy = second - rhs.second;
    return 1ll * dx * dx + 1ll * dy * dy;
  }
} a[maxn];

int n, vis[maxn];

bool check(const Node& a, const Node& b, const Node& c) {
  int x1 = a.first - b.first;
  int y1 = a.second - b.second;
  int x2 = c.first - b.first;
  int y2 = c.second - b.second;
  return 1ll * x1 * x2 + 1ll * y1 * y2 > 0;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    a[i].id = i;
  }
  vector<Node> ans { a[1] };
  for (int i = 1; i < n; i++) {
    ll mx = 0;
    int id = 0;
    for (int j = 2; j <= n; j++) {
      if (vis[j]) continue;
      if (i == 1 || check(ans[i - 2], ans[i - 1], a[j])) {
        if (ans[i - 1].dis(a[j]) > mx) {
          mx = ans[i - 1].dis(a[j]);
          id = j;
        }
      }
    }
    vis[id] = 1;
    ans.push_back(a[id]);
  }
  for (auto& x: ans) printf("%d ", x.id);
  return 0;
}
