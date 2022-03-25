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

int n, R, C, xx[maxn], yy[maxn], hh[maxn];

bool check(int n) {
  bool flag = (xx[1] + yy[1] + hh[1]) % 2;
  for (int i = 1; i <= n; i++) {
    if ((xx[i] + yy[i] + hh[i]) % 2 != flag) {
      return false;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (abs(hh[i] - hh[j]) > abs(xx[i] - xx[j]) + abs(yy[i] - yy[j])) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  scanf("%d%d%d", &n, &R, &C);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", xx + i, yy + i, hh + i);
  }
  for (int i = 1; i <= n; i++) {
    if (!check(i)) {
      printf("%d\n", i);
      return 0;
    }
  }
  puts("bravo komisijo");
  return 0;
}