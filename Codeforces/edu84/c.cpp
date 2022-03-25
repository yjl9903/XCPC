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

int n, m;

int main() {
  cin >> n >> m;
  if (n == 1 && m == 1) {
    puts("1\nU");
    return 0;
  }
  printf("%d\n", n + m - 2 + n * m - 1);
  for (int i = 1; i < m; i++) {
    putchar('L');
  }
  for (int i = 1; i < n; i++) {
    putchar('U');
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      putchar(i % 2 == 1 ? 'R' : 'L');
    }
    if (i < n) {
      putchar('D');
    }
  }
  return 0;
}