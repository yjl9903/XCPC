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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

ll h, x, y;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld%lld", &h, &x, &y);
    if (y == 0) {
      puts("No");
    } else if (x == 0) {
      puts("Yes");
    } else {
      if (h <= y) {
        puts("Yes");
      } else {
        ll rest = h % x, time = h / x;
        if (rest == 0) rest = x, time--;
        if (rest <= (time + 1) * y) {
          puts("Yes");
        } else {
          puts("No");
        }
      }
    }
  }
  return 0;
}