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

int n, k;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    if (k % 2 == n % 2 && n >= k) {
      puts("YES");
      printf("%d", n - k + 1);
      for (int i = 2; i <= k; i++) {
        printf(" 1");
      }
      puts("");
    } else if (n % 2 == 0 && n >= 2 * k) {
      puts("YES");
      printf("%d", n - 2 * k + 2);
      for (int i = 2; i <= k; i++) {
        printf(" 2");
      }
      puts("");
    } else {
      puts("NO");
    }
  }
  return 0;
}