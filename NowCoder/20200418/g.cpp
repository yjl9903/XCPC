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

int n, a[maxn]; ll m;

int main() {
  scanf("%d%lld", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + 1 + n);
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += a[i];
    if (sum > m) {
      printf("%d\n", i - 1);
      return 0;
    }
  }
  printf("%d\n", n);
  return 0;
}