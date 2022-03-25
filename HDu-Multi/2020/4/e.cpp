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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

string a[maxn];
char s[100];
int n, dp[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%s", s);
      a[i] = string(s);
    }
    dp[n] = dp[n + 1] = 1;
    for (int i = n - 1; i >= 1; i--) {
      dp[i] = dp[i + 1];
      if (a[i] != a[i + 1]) {
        dp[i] = (dp[i] + dp[i + 2]) % mod;
      }
    }
    printf("%d\n", dp[1]);
  }
  return 0;
}