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
    if (n <= 30) {
      puts("NO");
      continue;
    } else if (n == 36) {
      puts("YES");
      puts("5 6 10 15");
    } else if (n == 40) {
      puts("YES");
      puts("6 9 10 15");
    } else if (n == 44) {
      puts("YES");
      puts("6 7 10 21");
    } else {
      puts("YES");
      printf("6 10 14 %d\n", n - 30);
    }
  }
  return 0;
}