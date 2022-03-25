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
const int maxn = 5000 + 5;

int n, a[maxn], pre[maxn][maxn], suf[maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      suf[n + 1][i] = 0;
      for (int j = 1; j <= n; j++) {
        pre[i][j] = pre[i - 1][j];
      }
      pre[i][a[i]]++;
    }
    for (int i = n; i >= 1; i--) {
      for (int j = 1; j <= n; j++) {
        suf[i][j] = suf[i + 1][j];
      }
      suf[i][a[i]]++;
    }
    int flag = false;
    for (int i = 2; i < n; i++) {
      for (int j = 1; j <= n; j++) {
        if (pre[i - 1][j] && suf[i + 1][j]) {
          flag = true;
          break;
        }
      }
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}