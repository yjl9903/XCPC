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
const int maxn = 1000 + 5;

int n, a[maxn][maxn], ans[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    int tot = 0;
    for (int j = 1; j <= n; j++) {
      tot = a[i][j] | tot;
    }
    ans[i] = tot;
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", ans[i], i == n ? '\n' : ' ');
  }
  return 0;
}