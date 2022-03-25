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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    bool flag = false;
    for (int i = 2; 1ll * i * i <= n; i++) {
      if (n % i) continue;
      int x = n / i;
      for (int j = i + 1; 1ll * j * j <= x; j++) {
        if (x % j) continue;
        if (i != x / j && j != x / j && x / j > 1) {
          puts("YES");
          printf("%d %d %d\n", i, j, x / j);
          flag = true;
          break;
        }
      }
      if (flag) break;
    }
    if (!flag) {
      puts("NO");
    }
  }
  return 0;
}