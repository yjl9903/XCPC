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

int n, a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + 1 + n);
  printf("%d", a[(n + 1) / 2]);
  int x = (n + 1) / 2 - 1, y = (n + 1) / 2 + 1;
  while (x >= 1 || y <= n) {
    if (y <= n) {
      printf(" %d", a[y++]);
    }
    if (x >= 1) {
      printf(" %d", a[x--]);
    }
  }
  return 0;
}