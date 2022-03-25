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

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    if (n == 1) {
      puts("-1");
    } else {
      if ((2 * n + 1) % 3) {
        n--;
        while (n--) putchar('2');
        puts("3");
      } else {
        n -= 2;
        while (n--) putchar('2');
        puts("43");
      }
    }
  }
  return 0;
}