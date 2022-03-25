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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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

struct C {
  int x, y, r;
  int check(int a, int b) {
    return (x - a) * (x - a) + (y - b) * (y - b) <= r * r;
  }
};

int main() {
  vector<C> vec;
  for (int i = 1; i < 20; i++) {
    for (int j = 1; j < 20; j++) {
      for (int r = 1; r <= 10; r++) {
        if (i - r < 0 || i + r > 20 || j - r < 0 || j + r > 20) continue;
        vec.push_back({ i, j, r });
        dbg(i, j, r);
      }
    }
  }
  cout << vec.size() << endl;
  for (int i = 0; i <= 20; i++) {
    for (int j = 0; j <= 20; j++) {
      int cnt = 0;
      for (auto& x: vec) {
        if (x.check(i, j)) {
          cnt++;
        }
      }
      dbg(i, j, cnt);
    }
  }
  return 0;
}