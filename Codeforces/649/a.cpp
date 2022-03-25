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

int n, x, a[maxn], pre[maxn];
vector<int> pos[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &x);
    for (int i = 0; i < x; i++) pos[i].clear();
    pos[0].push_back(0);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      pre[i] = (pre[i - 1] + a[i]) % x;
      pos[pre[i]].push_back(i);
    }
    int ans = -1;
    for (int i = 0; i < x; i++) {
      if (pos[i].empty()) continue;
      int x = pos[i].front();
      int y = n;
      for (auto it = pos[i].rbegin(); it != pos[i].rend(); it++) {
        if (*it < y) break;
        y--;
      }
      if (x < y) ans = max(ans, y - x);
    }
    printf("%d\n", ans);
  }
  return 0;
}