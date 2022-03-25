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

PII sta[] = {
  { 5, 1 },
  { 5, 2 },
  { 3, 5 },
  { 4, 5 },
  { 3, 3 },
  { 1, 3 },
  { 3, 4 },
  { 1, 4 },
  { 3, 1 },
  { 2, 3 },
  { 2, 4 },
  { 1, 1 },
  { 1, 2 },
  { 2, 1 },
  { 2, 2 },
  { 3, 2 },
  { 4, 1 },
  { 4, 2 },
  { 4, 3 },
  { 1, 5 },
  { 2, 5 },
  { 4, 4 },
  { 5, 5 },
  { 5, 3 },
  { 5, 4 },
};

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    vector<int> a(5, 0), b(5, 0);
    for (int i = 0, x; i < 4; i++) {
      scanf("%d", &x);
      a[i] = x;
    }
    for (int i = 0, x; i < 4; i++) {
      scanf("%d", &x);
      b[i] = x;
    }

    auto print = [&]() {
      #ifdef XLor
        cout << "a:";
        for (int x: a) cout << ' ' << x;
        cout << endl;
        cout << "b:";
        for (int x: b) cout << ' ' << x;
        cout << endl;
      #endif
    };

    auto isLose = [&]() {
      return a[0] + a[1] + a[2] + a[3] + a[4] == 0;
    };
    auto isWin = [&]() {
      return b[0] + b[1] + b[2] + b[3] + b[4] == 0;
    };

    auto die = [&](vector<int>& v, int i) {
      v[i]--;
      if (i == 0) v[2]++;
      if (i == 1) v[3]++;
      if (i == 2) v[4]++;
    };

    auto run = [&](PII* st, vector<int>& a, vector<int>& b) {
      for (int i = 0; i < 25; i++) {
        int x = st[i].first - 1, y = st[i].second - 1;
        if (a[x] && b[y]) {
          if (x == 4 && (y == 2 || y == 3)) {
            die(a, 4);
          } else if ((x == 2 || x == 3) && y == 4) {
            die(b, 4);
          } else {
            die(a, x);
            die(b, y);
          }
          return true;
        }
      }
      return false;
    };

    while (!isLose() && !isWin()) {
      // dbg("Start");
      assert(run(sta, a, b));
      // print();
    }
    puts(isLose() ? "No" : "Yes");
  }  
  return 0;
}