#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int a, b, n, s;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &a, &b, &n, &s);
    if (1ll * a * n <= s) {
      s -= a * n;
      if (s <= b) puts("YES");
      else puts("NO");
    } else {
      int r = s % n;
      if (r <= b) puts("YES");
      else puts("NO");
    }
  }
  return 0;
}