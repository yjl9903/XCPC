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
const int maxn = 8000 + 5;

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1, sum = 0; i <= n; i++) {
      scanf("%d", a + i);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      bool flag = false;
      for (int h = 1, t = 1, sum = 0; t <= n; t++) {
        sum += a[t];
        while (h < t && sum > a[i]) {
          sum -= a[h++];
        }
        if (h < t && sum == a[i]) {
          flag = true;
          break;
        }
      }
      ans += flag;
    }
    printf("%d\n", ans);
  }
  return 0;
}