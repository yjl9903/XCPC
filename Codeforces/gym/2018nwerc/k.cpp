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

int n, m;
char a[maxn], b[maxn], key[maxn];

int main() {
  scanf("%d%d%s%s", &n, &m, a, b);
  for (int i = m - n; i < m; i++) {
    key[i + n] = a[i - m + n];
  }
  for (int i = m; i >= 0; i -= n) {
    for (int j = max(0, i - n); j < i; j++) {
      key[j] = (b[j] - key[j + n] + 26) % 26 + 'a';
    }
  }
  cout << key + n << endl;
  return 0;
}