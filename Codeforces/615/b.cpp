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
PII a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i].first, &a[i].second);
    }
    sort(a + 1, a + 1 + n);
    string ans;
    bool ok = true;
    int x = 0, y = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i].first >= x && a[i].second >= y) {
        while (x < a[i].first) ans += "R", x++;
        while (y < a[i].second) ans += "U", y++;
      } else {
        ok = false; break;
      }
    }
    if (ok) {
      puts("YES"); puts(ans.c_str());
    } else {
      puts("NO");
    }
  }
  return 0;
}