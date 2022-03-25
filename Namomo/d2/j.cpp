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
#include <bitset>
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
const int maxn = 1000 + 5;

int n, flag = true, b[maxn];
bitset<505> a;
vector<int> ans[maxn];

struct LinearBase {
  static const int maxl = 500;

  int cnt;
  bitset<maxl + 5> a[maxl + 5], pos[maxl + 5];

  void clear() {
    cnt = 0;
    for (int i = 0; i < maxl + 5; i++) {
      a[i].reset();
    }
  }
  LinearBase() { clear(); }

  bool insert(bitset<maxl + 5> x, int p) {
    bitset<maxl + 5> cur;
    cur.set(p);
    for (int i = maxl - 1; i >= 0; i--) {
      if (x[i]) {
        if (a[i].count()) {
          x ^= a[i];
          cur ^= pos[i];
        } else {
          a[i] = x;
          pos[i] = cur;
          cnt++;
          return true;
        }
      }
    }
    return false;
  }
  pair<bool, vector<int> > check(bitset<maxl + 5> x) {
    bitset<maxl + 5> cur;
    vector<int> ans;
    for (int i = maxl - 1; i >= 0; i--) {
      // dbg(x);
      if (x[i]) {
        if (a[i].count()) x ^= a[i], cur ^= pos[i];
        else return { false, ans };
      }
    }
    for (int i = 1; i <= n; i++) {
      if (cur[i]) {
        ans.push_back(i);
      }
    }
    return { true, ans };
  }
} lb;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    a.reset();
    for (int j = 0; j < n; j++) {
      scanf("%d", b + j);
      if (b[j]) {
        a.set(j);
      }
    }
    lb.insert(a, i);
  }
  for (int i = 0; i < n; i++) {
    a.reset();
    a.set(i);
    auto res = lb.check(a);
    if (res.first) {
      ans[i + 1] = res.second;
    } else {
      flag = false;
    }
  }
  if (flag) {
    for (int i = 1; i <= n; i++) {
      for (int x: ans[i]) printf("%d ", x);
      puts("");
    }
  } else {
    puts("-1");
  }
  return 0;
}