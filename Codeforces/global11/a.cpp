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
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      sum += a[i];
    }
    if (sum == 0) {
      puts("NO");
      continue;
    } else {
      sort(a + 1, a + 1 + n);
      if (sum > 0) reverse(a + 1, a + 1 + n);
      puts("YES");
      for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
      }
      puts("");
    }
  }
  return 0;
}