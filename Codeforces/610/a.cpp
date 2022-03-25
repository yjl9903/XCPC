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

int a, b, c, r;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &a, &b, &c, &r);
    if (a > b) swap(a, b);
    int ans = b - a;
    if (c - r <= a && c + r >= b) {
      ans = 0;
    } else if (c - r >= a && c + r <= b) {
      ans -= 2 * r;
    } else if (c - r <= b && c - r >= a) {
      ans -= b - (c - r);
    } else if (c + r >= a && c + r <= b) {
      ans -= (c + r) - a;
    }
    printf("%d\n", ans);
  }
  return 0;
}