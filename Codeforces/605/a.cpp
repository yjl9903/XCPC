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

int a, b, c;

ll cal(int a, int b, int c) {
  return abs(a - b) + abs(a - c) + abs(b - c);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &a, &b, &c);
    ll ans = cal(a, b, c);
    for (int i = a - 1; i <= a + 1; i++) {
      for (int j = b - 1; j <= b + 1; j++) {
        for (int k = c - 1; k <= c + 1; k++) {
          ans = min(ans, cal(i, j, k));
        }
      }
    }
    printf("%I64d\n", ans);
  }
  return 0;
}