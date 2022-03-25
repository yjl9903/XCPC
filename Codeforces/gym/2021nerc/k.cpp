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

const vector<PII> dir = { { 0, 0 }, {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int n;
char s[maxn];

bool solve(int bx, int by) {
  if (bx == 0 && by == 0) return false;
  int x = 0, y = 0;
  for (int i = 1; i <= n; i++) {
    int px = x, py = y;
    if (s[i] == 'L') {
      x--;
    } else if (s[i] == 'R') {
      x++;
    } else if (s[i] == 'D') {
      y--;
    } else if (s[i] == 'U') {
      y++;
    }
    if (x == bx && y == by) {
      x = px;
      y = py;
    }
  }
  return x == 0 && y == 0;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    bool flag = false;
    for (int i = 1, x = 0, y = 0; i <= n && !flag; i++) {
      if (s[i] == 'L') {
        x--;
      } else if (s[i] == 'R') {
        x++;
      } else if (s[i] == 'D') {
        y--;
      } else if (s[i] == 'U') {
        y++;
      }
      for (auto& d: dir) {
        if (solve(x + d.first, y + d.second)) {
          flag = true;
          printf("%d %d\n", x + d.first, y + d.second);
          break;
        }
      }
    }
    if (!flag) {
      puts("0 0");
    }
  }
  return 0;
}