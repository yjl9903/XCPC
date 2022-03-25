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

int c[maxn], a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    for (int i = 1; i <= 3; i++) {
      scanf("%d", c + i);
    }
    for (int i = 1; i <= 5; i++) {
      scanf("%d", a + i);
    }
    c[1] -= a[1];
    c[2] -= a[2];
    c[3] -= a[3];
    if (c[1] < 0 || c[2] < 0 || c[3] < 0) {
      puts("NO");
    } else {
      a[4] -= min(a[4], c[1]);
      a[5] -= min(a[5], c[2]);
      if (a[4] + a[5] <= c[3]) {
        puts("YES");
      } else {
        puts("NO");
      }
    }
  }
  return 0;
}