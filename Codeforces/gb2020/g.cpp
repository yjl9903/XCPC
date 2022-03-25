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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, m, q, pw2[maxn], sum[maxn][26];
char s[maxn], t[maxn], buf[maxn * 10];

int main() {
  pw2[0] = 1;
  for (int i = 1; i < maxn; i++) {
    pw2[i] = mul(pw2[i - 1], 2);
  }
  scanf("%d%d", &n, &q);
  scanf("%s%s", s, t);
  m = strlen(s);
  for (int j = 0; j < 26; j++) {
    for (int i = 1; i <= n; i++) {
      sum[i][j] = mul(sum[i - 1][j], 2);
      if (t[i - 1] == j + 'a') {
        sum[i][j] = add(sum[i][j], 1);
      }
    }
  }
  while (q--) {
    int k;
    scanf("%d%s", &k, buf);
    int len = strlen(buf);
    int ans = 0;
    for (int offset = 0; offset <= m; offset++) {
      string str;
      int cur = offset;
      bool ok = true;
      for (int i = 0; i < len; i++) {
        if (cur == m) {
          str += buf[i];
          cur = 0;
        } else {
          if (s[cur] != buf[i]) {
            ok = false;
            break;
          }
          cur++;
        }
      }
      if (!ok) continue;
      if (str.empty()) {
        ans = add(ans, pw2[k]);
        continue;
      }
      // dbg(offset, str);
      function<int(string,int)> solve = [&](string str, int cur) {
        if (cur >= k) return 0;
        if (str.size() == 1) {
          int c = str[0] - 'a';
          int ans = sum[k][c];
          ans = sub(ans, mul(sum[cur][c], pw2[k - cur]));
          return ans;
        }
        int ans = 0;
        {
          bool flag = true;
          for (int i = 0; i < str.size(); i += 2) {
            if (str[i] != t[cur]) {
              flag = false;
              break;
            }
          }
          if (flag) {
            string nxt;
            for (int i = 1; i < str.size(); i += 2) {
              nxt += str[i];
            }
            ans = add(ans, solve(nxt, cur + 1));
          }
        }
        {
          bool flag = true;
          for (int i = 1; i < str.size(); i += 2) {
            if (str[i] != t[cur]) {
              flag = false;
              break;
            }
          }
          if (flag) {
            string nxt;
            for (int i = 0; i < str.size(); i += 2) {
              nxt += str[i];
            }
            ans = add(ans, solve(nxt, cur + 1));
          }
        }
        return ans;
      };
      ans = add(ans, solve(str, 0));
    }
    printf("%d\n", ans);
  }
  return 0;
}