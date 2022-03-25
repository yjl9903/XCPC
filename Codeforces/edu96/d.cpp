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
const int maxn = 200000 + 5;

int n;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    int ans = 0;
    vector<int> a;
    for (int i = 1, j = 1; i <= n; i = j) {
      while (j <= n && s[i] == s[j]) j++;
      a.push_back(j - i);
    }
    int m = a.size();
    for (int i = 0; i < m; ) {
      if (a[i] > 1) {
        ans++;
        i++;
      } else {
        int j = i;
        while (j < m && a[j] == 1) j++;
        while (i < j) {
          assert(a[i] == 1);
          if (j < m) {
            i++;
            a[j]--;
            ans++;
            while (j < m && a[j] == 1) j++;
          } else {
            i += 2;
            ans++;
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}