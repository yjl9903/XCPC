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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    if (n == 2) {
      puts("1");
    } else if (n == 3) {
      puts("7");
    } else {
      if (n % 2) putchar('7'), n -= 3;
      n /= 2; while (n--) putchar('1');
      puts("");
    }
  }
  return 0;
}