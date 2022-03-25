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
const int maxn = 200000 + 5;

int n, pre[maxn][2];
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
      pre[i][0] = pre[i - 1][0];
      pre[i][1] = pre[i - 1][1];
      pre[i][s[i] - '0']++;
    }
    int ans = n + 1;
    for (int i = 0; i <= n; i++) {
      ans = min(ans, i - pre[i][1] + pre[n][1] - pre[i][1]);
      ans = min(ans, i - pre[i][0] + pre[n][0] - pre[i][0]);
    }
    printf("%d\n", ans);
  }
  return 0;
}