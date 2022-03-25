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
const int maxn = 200 + 5;

int n, m, dp[55][205];
vector<PII> plans[55];

int main() {
  dp[0][0] = true;
  for (int i = 1; i <= 50; i++) {
    set<int> st;
    for (int a = 1; a <= i; a++) {
      for (int b = a; b <= i; b++) {
        if (i >= a + b - 1 && a * b >= i) {
          if (!st.count(a + b)) {
            st.insert(a + b);
            plans[i].emplace_back(a, b);
            for (int x = 0; x + i <= 50; x++) {
              for (int y = 0; y + 2 * (a + b) <= 200; y++) {
                dp[x + i][y + 2 * (a + b)] |= dp[x][y];
              }
            }
          }
        }
      }
    }
  }
  for (int i = 1; i <= 50; i++) {
    vector<int> vec;
    for (int j = 1; j <= 4 * i; j++) {
      if (dp[i][j]) vec.push_back(j);
    }
  }
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    int N = n;
    if (dp[n][m]) {
      vector< tuple<int,int,int> > ans;
      while (n > 0 && m > 0) {
        bool ok = false;
        for (int i = n; i >= 1 && !ok; i--) {
          for (auto& x: plans[i]) {
            int nn = n - i;
            int mm = m - 2 * (x.first + x.second);
            if (nn >= 0 && mm >= 0 && dp[nn][mm]) {
              n = nn;
              m = mm;
              ans.emplace_back(i, x.first, x.second);
              ok = true;
              break;
            }
          }
        }
      }
      assert(n == 0 && m == 0);
      puts("Yes");
      int cnt = 0, baseX = 0, baseY = 0;
      auto print = [&](int x, int y) {
        printf("%d %d\n", x + baseX, y + baseY);
        cnt++;
      };
      for (auto& rect: ans) {
        int cnt = 0, n, a, b; tie(n, a, b) = rect;
        // dbg(n, a, b);
        for (int i = 0; i < a; i++) {
          print(0, i); cnt++;
        }
        for (int r = 0; r < a; r++) {
          for (int c = 1; c < b && cnt < n; c++, cnt++) {
            print(c, r);
          }
        }
        baseX += 1000;
      }
      assert(cnt == N);
    } else {
      puts("No");
    }
  }
  return 0;
}