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

int r, b, k;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &r, &b, &k);
    int g = __gcd(r, b);
    r /= g; b /= g;
    if (r > b) swap(r, b);
    if (b <= 2) puts("OBEY");
    else {
      int mx = (b - 1 + r - 1) / r;
      if (mx >= k) puts("REBEL");
      else puts("OBEY");
    }
  }
  return 0;
}