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

int n, k;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%s", &n, &k, s + 1);

    int ans = 0;
    vector<int> a;
    vector<PII> v[3];
    if (s[1] == 'L') a.push_back(0);
    for (int i = 1, j = 1; i <= n; i = j) {
      while (j <= n && s[i] == s[j]) j++;
      a.push_back(j - i);
      if (a.size() % 2 == 0) {
        int d = 0;
        int val = (j - i) * 2 - 1;
        if (s[i - 1] == 'W') d++;
        if (s[j] == 'W') d++;
        v[d].emplace_back(j - i, val + d);
        // dbg(i, j, val, d);
      } else {
        ans += (j - i) * 2 - 1;
      }
    }

    for (int i = 2; i >= 0 && k; i--) {
      sort(begin(v[i]), end(v[i]));
      for (auto x: v[i]) {
        if (k == 0) break;
        if (k >= x.first) {
          k -= x.first;
          ans += x.second;
        } else {
          ans += k * 2 - 1;
          if (i) ans++;
          k = 0;
        }
      }
    }

    printf("%d\n", ans);
  }
  return 0;
}