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
      puts("26");
    } else if (n == 2) {
      puts("676");
    } else if (n == 3) {
      puts("17576");
    } else {
      int base = 26 * 25 * 24;
      printf("%d\n", base);
    }
  }
  return 0;
}