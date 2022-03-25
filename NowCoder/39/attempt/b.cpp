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

int n, k;
char s[maxn];

int getmin(char* s) {
  int i = 0, j = 1, k = 0;
  while (i < n && j < n && k < n) {
    int t = s[(i + k) % n] - s[(j + k) % n];
    if (!t) k++;
    else {
      if (t > 0) i += k + 1;
      else j += k + 1;
      if (i == j) j++;
      k = 0;
    }
  }
  return min(i, j) + 1;
}

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  int p = getmin(s + 1);
  rotate(s + 1, s + p, s + 1 + n);
  string ans;
  for (int i = 1; i <= n; i += k) {
    string tot;
    for (int j = i; j < i + k; j++) tot += s[j];
    if (i == 1 || tot > ans) ans = tot;
  }
  puts(ans.c_str());
  return 0;
}