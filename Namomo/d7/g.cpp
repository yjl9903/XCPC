#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#ifdef XLor
#define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
void err() { std::cout << "\033[39;0m" << std::endl; }
template <typename T, typename... Args>
void err(T a, Args... args) {
  std::cout << a << ' ';
  err(args...);
}
#else
#define dbg(...)
#endif
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k, mn[maxn][2], mx[maxn][2];
char s[maxn], t[maxn];

string solve(int k, char s[]) {
  // dbg(s + 1);
  mn[n + 1][0] = mn[n + 1][1] = 0;
  mx[n + 1][0] = mx[n + 1][1] = 0;
  for (int i = n; i >= 1; i--) {
    if (s[i] == '0') {
      mn[i][0] = min(mn[i + 1][0], mn[i + 1][1] + 1);
      mn[i][1] = inf;
      mx[i][0] = max(mx[i + 1][0], mx[i + 1][1] + 1);
      mx[i][1] = -inf;
    } else if (s[i] == '1') {
      mn[i][0] = inf;
      mn[i][1] = min(mn[i + 1][0] + 1, mn[i + 1][1]);
      mx[i][0] = -inf;
      mx[i][1] = max(mx[i + 1][0] + 1, mx[i + 1][1]);
    } else if (s[i] == '?') {
      mn[i][0] = min(mn[i + 1][0], mn[i + 1][1] + 1);
      mn[i][1] = min(mn[i + 1][0] + 1, mn[i + 1][1]);
      mx[i][0] = max(mx[i + 1][0], mx[i + 1][1] + 1);
      mx[i][1] = max(mx[i + 1][0] + 1, mx[i + 1][1]);
    }
  }
  bool flag = true;
  for (int i = 1; i <= n; i++) {
    // dbg(i, k, s + 1);
    if (s[i] == '?') {
      auto check = [&](int x, int k) {
        if (i == n) {
          return k == 0;
        } else {
          for (int j = 0; j < 2; j++) {
            int cur = k;
            cur -= int(x != j);
            if (mn[i + 1][j] <= cur && cur <= mx[i + 1][j]) {
              return true;
            }
          }
          return false;
        }
      };
      if (check(0, k - int(i > 1 && s[i - 1] == '1'))) {
        s[i] = '0';
      } else if (check(1, k - int(i > 1 && s[i - 1] == '0'))) {
        s[i] = '1';
      } else {
        flag = false;
        break;
      }
    }
    if (i > 1) {
      k -= int(s[i] != s[i - 1]);
    }
  }
  if (flag && k == 0) {
    // puts(s + 1);
    return s + 1;
  } else {
    // puts("Impossible");
    return "";
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%s", &n, &k, s + 1);
    string ans;
    for (int i = 0; i < 2; i++) {
      if (s[1] == '?') {
        t[1] = i + '0';
      } else {
        t[1] = s[1];
      }
      for (int j = 0; j < 2; j++) {
        if (s[n] == '?') {
          t[n] = j + '0';
        } else {
          t[n] = s[n];
        }
        for (int i = 2; i < n; i++) t[i] = s[i];
        t[n + 1] = 0;
        auto res = solve(k, t);
        // dbg(res);
        if (!res.empty()) {
          if (ans.empty() || res < ans) {
            ans = res;
          }
        }
      }
    }
    if (!ans.empty()) {
      puts(ans.c_str());
    } else {
      puts("Impossible");
    }
  }
  return 0;
}