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
const int maxn = 200000 + 5;

int n;

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    vector<PII> ans;
    if (n >= 40) {
      n -= 40;
      int col = 1, rest = 0;
      for (int h = 1; h <= 30; h++) {
        if (n >> (h - 1) & 1) {
          if (col == 1) {
            for (; col <= h; col++) {
              ans.emplace_back(h, col);
            }
            col--;
          } else if (col == h) {
            for (; col >= 1; col--) {
              ans.emplace_back(h, col);
            }
            col++;
          }
          n -= 1 << (h - 1);
        } else {
          ans.emplace_back(h, col);
          rest++;
        }
        if (col == h) col++;
      }
      assert(n == 0);
      n += 40 - rest;
      for (int h = 31; n > 0; h++, n--) {
        ans.emplace_back(h, col);
        if (col == h) col++;
      }
      assert(n == 0);
    } else {
      for (int i = 1; i <= n; i++) {
        ans.emplace_back(i, 1);
      }
    }
    assert(ans.size() <= 500);
    printf("Case #%d:\n", ++kase);
    for (auto& x: ans) {
      printf("%d %d\n", x.first, x.second);
    }
  }
  return 0;
}