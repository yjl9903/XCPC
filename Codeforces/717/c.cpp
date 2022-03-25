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

int n, a[maxn], f[maxn];

int main() {
  scanf("%d", &n);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    sum += a[i];
  }
  f[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = sum; j >= a[i]; j--) {
      f[j] |= f[j - a[i]];
    }
  }
  if (sum % 2 == 1 || !f[sum / 2]) {
    return puts("0"), 0;
  }
  int g = a[1];
  for (int i = 2; i <= n; i++) {
    g = __gcd(a[i], g);
  }
  for (int i = 1; i <= n; i++) {
    a[i] /= g;
    if (a[i] % 2 == 1) {
      puts("1");
      printf("%d\n", i);
      return 0;
    }
  }
  assert(false);
  return 0;
}