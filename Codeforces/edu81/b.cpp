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

int n, x, pre[maxn];
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%s", &n, &x, s + 1);
    for (int i = 1; i <= n; i++) {
      pre[i] = pre[i - 1];
      if (s[i] == '0') pre[i]++;
      else if (s[i] == '1') pre[i]--;
    }
    if (pre[n] == 0) {
      int ans = 0;
      for (int i = 1; i <= n; i++) {
        if (pre[i] == x) {
          ans++; break;
        }
      }
      if (ans) puts("-1");
      else puts("0");
    } else {
      int ans = 0;
      if (x == 0) ans++;
      for (int i = 1; i <= n; i++) {
        if (pre[n] < 0) {
          if (pre[i] >= x && (pre[i] - x) % (-pre[n]) == 0) {
            ans++;
          }
        } else if (pre[n] > 0) {
          if (pre[i] <= x && (x - pre[i]) % pre[n] == 0) {
            ans++;
          }
        }
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}