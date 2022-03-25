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
const int maxn = 100000 + 5;

int x, y, a, b;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &x, &y, &a, &b);
    if ((y - x) % (a + b) == 0) {
      printf("%d\n", (y - x) / (a + b));
    } else {
      puts("-1");
    }
  }
  return 0;
}