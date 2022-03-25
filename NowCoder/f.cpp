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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int inv(int a, int m) {
  a %= m;
  if (a < 0) {
    a += m;
  }
  int b = m, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= a * t;
    swap(a, b);
    u -= v * t;
    swap(u, v);
  }
  if (u < 0) {
    u += m;
  }
  return u;
}

int p;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &p);
    if (p == 2) {
      puts("0"); continue;
    } else if (p == 3) {
      puts("1"); puts("2 2"); continue;
    }
    int mn = inv(2, p);
    vector<PII> ans = { { 2, mn } };
    for (int i = 3; i < mn; i++) {
      int f = inv(i, p);
      mn = min(f, mn);
      if (f == mn) {
        ans.push_back({ i, f });
      }
    }
    printf("%d\n", 2 * ans.size());
    for (auto& x: ans) {
      printf("%d %d\n", x.first, x.second);
    }
    reverse(begin(ans), end(ans));
    for (auto& x: ans) {
      printf("%d %d\n", x.second, x.first);
    }
  }
  return 0;
}