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
const int maxn = 2000000 + 5;

char s[maxn];
int n, q;

int main() {
  scanf("%s", s);
  n = strlen(s);
  scanf("%d", &q);
  int offset = 0;
  auto get = [&](int i) {
    return ((i + offset) % n + n) % n;
  };
  for (int i = 0; i < q; i++) {
    char op[3]; int x;
    scanf("%s%d", op, &x);
    if (op[0] == 'M') {
      offset += x;
    } else if (op[0] == 'A') {
      dbg(offset % n);
      printf("%c\n", s[get(x - 1)]);
    }
  }
  return 0;
}