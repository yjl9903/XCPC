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
const int maxn = 500 + 5;

int n, m, ans[maxn][maxn];

int main() {
  scanf("%d%d", &n, &m);
  if (n == 1 && m == 1) {
    puts("0"); return 0;
  } else if (n == 1) {
    for (int i = 1; i <= m; i++) {
      printf("%d ", i + 1);
    }
    return 0;
  } else if (m == 1) {
    for (int i = 1; i <= n; i++) {
      printf("%d\n", i + 1);
    }
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans[i][j] = i * (n + j);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      printf("%d ", ans[i][j]);
    }
    puts("");
  }
  return 0;
}