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

int a, b, dp[maxn][maxn];

int cal(int a, int b) {
  return __gcd(a, b) == 1;
}

int main() {
  dp[1][1] = 1;
  for (int i = 1; i <= 1000; i++) {
    for (int j = 1; j <= 1000; j++) {
      dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + cal(i + 1, j));
      dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + cal(i, j + 1));
    }
  }
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &a, &b);
    printf("%d\n", dp[a][b]);
  }
  return 0;
}