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

int n, x, a[maxn];

int main() {
  scanf("%d%d", &n, &x);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (a[j] - a[j - 1] <= x) {
        ans = max(ans, j - i + 1);
      } else {
        break;
      }
    }
  }
  cout << ans;
  return 0;
}