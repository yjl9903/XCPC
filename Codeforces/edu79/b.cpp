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

int n, s, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    ll sum = 0; int mx = 0, pos = 0, ans = 0;
    int ok = 0;
    for (int i = 1; i <= n; i++) {
      sum += a[i];
      if (a[i] > mx) mx = a[i], pos = i;
      if (sum > s) {
        if (sum - mx <= s) {
          ans = pos;
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}