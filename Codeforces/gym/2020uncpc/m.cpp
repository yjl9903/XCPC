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

char s[maxn];
int n, q, cnt[30], nxt[maxn][26];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    cnt[s[i] - 'a']++;
  }
  for (int i = 0; i < 26; i++) nxt[n][i] = nxt[n + 1][i] = n + 1;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
    nxt[i][s[i + 1] - 'a'] = i + 1;
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    scanf("%s", s + 1);
    int m = strlen(s + 1);
    if (cnt[s[1] - 'a']) {
      int u = 0;
      for (int i = 1; i <= m; i++) {
        if (nxt[u][s[i] - 'a'] <= n) {
          putchar(s[i]);
          u = nxt[u][s[i] - 'a'];
        } else {
          break;
        }
      }
      puts("");
    } else {
      puts("IMPOSSIBLE");
    }
  }
  return 0;
}