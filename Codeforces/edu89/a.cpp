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

int a, b;

int get(int a, int b) {
  int sum = min(a, b / 2);
  a -= sum; b -= sum + sum;
  return sum + min(a / 2, b);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &a, &b);
    int r1 = max(get(a, b), get(b, a));
    int x1 = max((a + a - b) / 3, 0), x2 = max((b + b - a) / 3, 0);
    for (int i = x1; i <= x1 + 2; i++) {
      for (int j = x2; j <= x2 + 2; j++) {
        if (i + i + j <= a && i + j + j <= b) {
          r1 = max(r1, i + j);
        }
      }
    }
    printf("%d\n", r1);
  }
  return 0;
}