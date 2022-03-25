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
#include <ctime>
#include <random>
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

mt19937 rnd(time(nullptr));

struct Node {
  int first, second, id;

  bool operator< (const Node& rhs) const {
    if (second != rhs.second) {
      return second < rhs.second;
    } else {
      return first < rhs.first;
    }
  }
} a[maxn];

int n;

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
  clock_t now = clock();
  bool flag = true;
  while (clock() - now < 1900) {
    shuffle(a + 1, a + 1 + n, rnd);
    flag = true;
    for (int i = 3; i <= n; i++) {
      if (!check(a[i - 2], a[i - 1], a[i])) {
        flag = false;
        break;
      }
    }
    if (flag) break;
  }
  assert(flag);
  for (int i = 1; i <= n; i++) {
    printf("%d ", a[i].id);
  }
  return 0;
}