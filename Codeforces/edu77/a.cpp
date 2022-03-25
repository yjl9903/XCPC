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

int c, sum;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &c, &sum);
    if (c >= sum) {
      printf("%d\n", sum);
    } else {
      vector<int> v(c, sum / c);
      for (int i = sum / c * c + 1, j = 0; i <= sum; i++, j++) v[j]++;
      ll ans = 0;
      for (int x: v) {
        ans += 1ll * x * x;
      }
      printf("%I64d\n", ans);
    }
  }
  return 0;
}