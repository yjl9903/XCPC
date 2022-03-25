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

int qpow(int x, int n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x;
    n >>= 1; x = 1ll * x * x;
  }
  return r;
}

int n;

int main() {
  scanf("%d", &n);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    char op[3]; int m;
    scanf("%s%d", op, &m);
    if (op[0] == 'S') {
      ans = max(ans, m);
    } else if (op[0] == 'M') {
      ans = max(ans, qpow(2, m) - 1);
    }
  }
  printf("%d\n", ans);
  return 0;
}