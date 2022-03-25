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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

char s[maxn];
int n, q;

int duval(char s[], int n) {
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
      // printf("%d ", i + k - j - 1);
      return i + k - j - 1;
      // i += k - j;
    }
  }
  return n;
}

int ans[maxn];

int main() {
  scanf("%s%d", s + 1, &q);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    ans[n - i + 1] = n - i + duval(s + n - i, i);
  }
  // for (int i = 1; i <= n; i++) dbg(i, ans[i]);
  for (int i = 1, l, k; i <= q; i++) {
    scanf("%d%d", &l, &k);
    if (k == 1) {
      printf("%d %d\n", l, n);
    } else {
      printf("%d %d\n", l, ans[l]);
    }
  }
  return 0;
}