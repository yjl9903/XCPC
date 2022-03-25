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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
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
const int maxn = 10000 + 5;

int main() {
  int T; cin >> T;
  while (T--) {
    ll a, b; cin >> a >> b;
    if (a == b) {
      puts("0"); continue;
    }
    int d = abs(a - b), tot = 1, sum = 0;
    while (true) {
      sum += tot;
      if (sum >= d && (sum - d) % 2 == 0) {
        break;
      }
      tot++;
    }
    printf("%d\n", tot);
  }
  return 0;
}