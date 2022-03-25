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

char s[maxn], t[maxn];
int n, m;

int main() {
  cin.getline(s, maxn);
  cin.getline(t, maxn);
  n = strlen(s);
  m = strlen(t);
  dbg(s);
  dbg(t);
  set<char> ans;
  for (int i = 0, j = 0, p = 0, q = 0; i < n && p < m; i = j, p = q) {
    // dbg(i, s[i]);
    // dbg(p, t[p]);
    while (j < n && s[j] == s[i]) j++;
    while (q < m && t[q] == t[p]) q++;
    if (j - i != q - p) {
      assert(q - p == 2 * (j - i));
      ans.insert(s[i]);
    }
  }
  for (char x: ans) {
    putchar(x);
  }
  return 0;
}