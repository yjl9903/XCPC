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
#include <cstdlib>
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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, sum[maxn];
char s[maxn];

bool isAll0(int l, int r) {
  if (l > r) return true;
  return sum[r] - sum[l - 1] == 0;
}
bool isAll9(int l, int r) {
  if (l > r) return true;
  return sum[r] - sum[l - 1] == (r - l + 1) * 9;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);

    char mx = s[1], mn = s[1];
    for (int i = 1; i <= n; i++) {
      mx = max(mx, s[i]);
      mn = min(mn, s[i]);
      sum[i] = sum[i - 1] + (s[i] - '0');
    }
    int ans = mx - mn;

    if (s[1] != '0') {
      function<int(int)> checkP = [&](int len) {
        vector<int> mx, mn;
        for (int i = 1; i <= len; i++) {
          mx.push_back(s[i] - '0');
          mn.push_back(s[i] - '0');
        }
        for (int j = len + 1; j + len - 1 <= n; j += len) {
          vector<int> tot;
          if (s[j] == '0') return 10;
          for (int k = 0; k < len; k++) {
            tot.push_back(s[j + k] - '0');
          }
          if (tot < mn) mn = vector<int>(tot);
          if (mx < tot) mx = vector<int>(tot);
        }
        vector<int> vec(len, 0);
        for (int i = len - 1; i >= 0; i--) {
          if (mx[i] >= mn[i]) {
            vec[i] = mx[i] - mn[i];
          } else {
            vec[i] = 10 + mx[i] - mn[i];
            mx[i - 1]--;
          }
        }
        for (int i = 0; i + 1 < len; i++) {
          if (vec[i]) {
            return 10;
          }
        }
        return vec[len - 1];
      };

      for (int i = 2; i + i <= n; i++) {
        if (n % i == 0) {
          // ans = min(ans, checkP(i));
        }
      }

      checkP = [&](int len) {
        int i = 1, mx = -10000, mn = 10000;
        while (i <= n) {
          if (s[i] == '1') {
            // '1' + (len - 1) * '0' + x
            if (i + len > n) return 10;
            if (!isAll0(i + 1, i + len - 1)) return 10;
            int tot = s[i + len] - '0';
            // mx = max(mx, tot);
            mn = min(mn, tot);
            i += len + 1;
          } else {
            // (len - 1) * '9' + x
            if (i + len - 1 > n) return 10;
            if (!isAll9(i, i + len - 2)) return 10;
            int tot = s[i + len - 1] - '0';
            if (mx < 0) {
              assert(tot - 10 <= 10);
            }
            // mx = max(mx, tot - 10);
            mn = min(mn, tot - 10);
            i += len;
          }
        }
        if (mx < 0 || mn > 0) return 10;
        assert(mx - mn >= 0 && mx - mn <= 19);
        return mx - mn;
      };

      for (int i = 1; i + i <= n; i++) {
        ans = min(ans, checkP(i));
      }
    }

    printf("%d\n", ans);
  }
  return 0;
}