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
const int maxn = 10000 + 5;

int n, m, x, y;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &x, &y);
    if (y > x + x) y = x + x;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%s", s + 1);
      for (int i = 1; i <= m; i++) {
        if (i + 1 <= m && s[i] == '.' && s[i + 1] == '.') {
          ans += y; i++;
        } else if (s[i] == '.') {
          ans += x;
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}