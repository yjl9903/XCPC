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
const int maxn = 1000000 + 5;

int n, xs[maxn], ans[maxn];
char s[maxn];

int nxt[maxn];
void getnxt(int n, char* s) {
  int p = 1, k = 2; nxt[1] = n;
  while (p + 1 <= n && s[p] == s[p + 1]) p++;
  nxt[2] = p - 1;
  for (int i = 3; i <= n; i++) {
    int len = nxt[i - k + 1];
    if (len + i <= p) nxt[i] = len;
    else {
      int j = max(p - i + 1, 0);
      while (i + j <= n && s[j + 1] == s[i + j]) j++;
      nxt[i] = j; k = i;
      p = i + j - 1;
    }
  }
}

int main() {
  xs[0] = 1;
  for (int i = 1; i < maxn; i++) xs[i] = 1ll * 1112 * xs[i - 1] % mod;
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    auto solve = [&](int L, int R) {
      getnxt(R - L + 1, s + L - 1);
      ans[L] = L;
      vector<int> stk = { 1 };
      for (int i = L + 1; i <= R; i++) {
        while (!stk.empty() && (i - L + 1) + nxt[i - L + 1] > stk.back() + nxt[stk.back()]) {
          stk.pop_back();
        }
        stk.push_back(i - L + 1);
        while (!stk.empty() && nxt[stk.back()] <= i - (L + stk.back() - 1)) stk.pop_back();
        ans[i] = L - 1 + stk.back();
      }
    };
    for (int i = 1, j, k; i <= n; ) {
      j = i; k = i + 1;
      while (k <= n && s[j] <= s[k]) {
        if (s[j] < s[k]) {
          j = i;
        } else {
          j++;
        }
        k++;
      }
      while (i <= j) {
        solve(i, i + k - j - 1);;
        i += k - j;
      }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
      res = (res + 1ll * xs[i - 1] * ans[i] % mod) % mod;
    }
    printf("%d\n", res);
  }
  return 0;
}