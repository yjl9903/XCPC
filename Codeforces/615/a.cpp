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

int a, b, c, n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &a, &b, &c, &n);
    int mx = max(a, max(b, c));
    int sum = mx - a + mx - b + mx - c;
    if (n >= sum) {
      n -= sum;
      if (n % 3 == 0) puts("YES");
      else puts("NO");
    } else {
      puts("NO");
    }
  }
  return 0;
}