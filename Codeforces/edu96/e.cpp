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

int n;
char s[maxn];
vector<int> bag[30];

struct BIT {
  int a[maxn];
  void update(int i) {
    for (; i <= n; i += i & -i) a[i]++;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int L, int R) {
    if (L <= R) {
      return query(R) - query(L - 1);
    } else {
      return 0;
    }
  }
} f;

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; i++) {
    bag[s[i] - 'a'].push_back(i);
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    int pos = bag[s[i] - 'a'].back();
    bag[s[i] - 'a'].pop_back();
    int val = n - pos - f.query(pos + 1, n);
    ans += val;
    dbg(i, val);
    f.update(pos);
  }
  printf("%I64d\n", ans);
  return 0;
}