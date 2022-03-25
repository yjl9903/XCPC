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

int n, k1, k2, a[maxn], b[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &k1, &k2);
    int mx1 = 0, mx2 = 0;
    for (int i = 1; i <= k1; i++) {
      scanf("%d", a + i);
      mx1 = max(a[i], mx1);
    }
    for (int i = 1; i <= k2; i++) {
      scanf("%d", b + i);
      mx2 = max(b[i], mx2);
    }
    if (mx1 > mx2) puts("YES");
    else puts("NO");
  }
  return 0;
}