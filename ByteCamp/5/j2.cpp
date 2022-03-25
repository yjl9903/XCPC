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
#include <random>
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

int n, q, k, s, a[maxn], pos[maxn];

bool check(int x, int l, int r) {
  if (x >= n) return false;
  return l <= pos[x] && pos[x] <= r;
}
int query(int l, int r) {
  if (r - l + 1 == n) {
    return n;
  }
  int ans = 0;
  while (check(ans, l, r)) ans++;
  return ans;
}

int main() {
  scanf("%d%d%d%d", &n, &q, &k, &s);
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
    pos[a[i]] = i;
  }
  mt19937 gen; gen.seed(s);
  int last = 0;
  while (q--) {
    int op = gen() % k;
    int i = (gen() + last) % n;
    if (!op && i) {
      // dbg("op1", i);
      swap(a[i - 1], a[i]);
      pos[a[i - 1]] = i - 1;
      pos[a[i]] = i;
    } else {
      // dbg("op2");
      int j = gen() % n;
      if (i > j) swap(i, j);
      // dbg(i, j, query(i, j));
      last ^= query(i, j);
    }
  }
  printf("%d\n", last);
  return 0;
}