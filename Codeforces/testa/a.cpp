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

int n, a, b;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &a, &b);
    if (b == 1) {
      if (n == 1) {
        puts("Yes");
      } else {
        puts("No");
      }
    } else {
      b--;
      int need = (n + b - 2) / b;
      if (a >= need) {
        puts("Yes");
      } else {
        puts("No");
      }
    }
  }
  return 0;
}