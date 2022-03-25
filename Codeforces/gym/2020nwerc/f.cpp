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
#include <queue>
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

int n, x[maxn], v[maxn];

struct Node {
  ll fz, fm;
  int a, b;

  bool operator< (const Node& rhs) const {
    return 1ll * fz * rhs.fm > 1ll * fm * rhs.fz;
  }
};

int main() {
  scanf("%d", &n);
  set<int> live;
  priority_queue<Node> pq;
  auto push = [&](int i, int j) {
    if (v[i] != v[j] && 1ll * (x[j] - x[i]) * (v[i] - v[j]) > 0) {
      pq.push({ 1ll * x[j] - x[i], 1ll * v[i] - v[j], i, j });
    }
  };
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", x + i, v + i);
    live.insert(i);
    if (i > 1) {
      push(i - 1, i);
    }
  }
  while (!pq.empty()) {
    auto u = pq.top();
    pq.pop();
    if (!live.count(u.a) || !live.count(u.b)) continue;
    live.erase(u.a);
    live.erase(u.b);

    auto it = live.upper_bound(u.b);
    int L = -1, R = -1;
    if (it != live.end()) {
      R = *it;
    }
    if (it != live.begin()) {
      it--;
      L = *it;
    }

    if (L != -1 && R != -1) {
      assert(L < u.a && R > u.b);
      push(L, R);
    }
  }
  printf("%d\n", live.size());
  for (int x: live) printf("%d ", x);
  return 0;
}