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

int n, a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 3; i <= n; i++) {
    int x = __lg(a[i - 2]);
    int y = __lg(a[i - 1]);
    int z = __lg(a[i]);
    if (x == y && y == z) {
      puts("1");
      return 0;
    }
  }
  int ans = inf;
  for (int i = 1; i <= n; i++) {
    int L = 0;
    for (int j = i; j >= 1; j--) {
      L ^= a[j];
      int R = 0;
      for (int k = i + 1; k <= n; k++) {
        R ^= a[k];
        if (L > R) {
          ans = min(ans, i - j + k - i - 1);
        }
      }
    }
  }
  if (ans == inf) {
    puts("-1");
  } else {
    printf("%d\n", ans);
  }
  return 0;
}