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

int r, b;

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &r, &b);
    int fm = (r + b) * (r + b - 1) / 2;
    int fz = r * (r - 1) / 2;
    int g = __gcd(fz, fm);
    printf("Case #%d: %d/%d\n", ++kase, fz / g, fm / g);
  }
  return 0;
}