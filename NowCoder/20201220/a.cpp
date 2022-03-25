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

bool check1() {
  int d = a[2] - a[1];
  for (int i = 3; i <= n; i++) {
    if (a[i] - a[i - 1] != d) {
      return false;
    }
  }
  return true;
}
bool check2() {
  for (int i = 3; i <= n; i++) {
    if (1ll * a[i] * a[i - 2] != 1ll * a[i - 1] * a[i - 1]) {
      return false;
    }
  }
  return true;
}
bool check3() {
  for (int i = 3; i <= n; i++) {
    if (a[i] % a[i - 1] != a[i - 1] % a[i - 2]) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  if (check1() || check2() || check3()) {
    puts("YES");
  } else {
    puts("NO");
  }
  return 0;
}