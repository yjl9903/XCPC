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

int n, m, nxt[maxn][26];
char s[maxn], t[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1); m = strlen(t + 1);
    for (int i = 0; i < 26; i++) {
      nxt[n][i] = nxt[n + 1][i] = n + 1;
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
      nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    int ans = 1;
    for (int i = 1, u = 0; i <= m; i++) {
      int nx = nxt[u][t[i] - 'a'];
      if (nx > n) {
        u = nxt[0][t[i] - 'a']; ans++;
        if (u > n) {
          ans = -1; break;
        }
      } else {
        u = nx;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}