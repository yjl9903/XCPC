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

int n;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int px = 0, py = 0;
    int cl = 0, cr = 0, cu = 0, cd = 0;
    for (int i = 1; i <= n; i++) {
      if (s[i] == 'L') px--, cl++;
      if (s[i] == 'R') px++, cr++;
      if (s[i] == 'U') py++, cu++;
      if (s[i] == 'D') py--, cd++;
    }
    int ans = 0;
    if (px < 0) ans -= px, cl += px;
    else if (px > 0) ans += px, cr -= px;
    if (py < 0) ans -= py, cd += py;
    else if (py > 0) ans += py, cu -= py;
    if (!cl || !cr || !cu || !cd) {
      if (cl && cr) {
        puts("2");
        puts("LR");
      } else if (cu && cd) {
        puts("2");
        puts("UD");
      } else {
        puts("0");
      }
      continue;
    }
    printf("%d\n", n - ans);
    while (cr--) putchar('R');
    while (cu--) putchar('U');
    while (cl--) putchar('L');
    while (cd--) putchar('D');
    puts("");
  }
  return 0;
}