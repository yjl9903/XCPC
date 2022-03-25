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

int n, nxt[maxn][3];
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    nxt[n][0] = nxt[n][1] = nxt[n][2] = n + 1;
    nxt[n + 1][0] = nxt[n + 1][1] = nxt[n + 1][2] = n + 1;
    for (int i = n - 1; i >= 0; i--) {
      nxt[i][0] = nxt[i + 1][0];
      nxt[i][1] = nxt[i + 1][1];
      nxt[i][2] = nxt[i + 1][2];
      nxt[i][s[i + 1] - '1'] = i + 1;
    }
    int ans = inf;
    for (int i = 1; i + 2 <= n; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          if (j == k) continue;
          if (s[i] - '1' == j) continue;
          if (s[i] - '1' == k) continue;
          int u1 = i;
          int u2 = nxt[u1][j];
          int u3 = nxt[u2][k];
          if (u2 == n + 1 || u3 == n + 1) continue;
          ans = min(ans, u3 - i + 1);
        }
      }
    }
    if (ans == inf) puts("0");
    else printf("%d\n", ans);
  }
  return 0;
}