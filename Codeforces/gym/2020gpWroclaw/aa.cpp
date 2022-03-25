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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;
const int maxk = 3000 + 5;

struct Ope {
  int tp, pos;
  char ch;
};

int n, m, k;
int f[maxk][maxk];
char buf[maxn];

int lcp(int x, int y) {
  int ans = 0;
  while (ans <= n && ans <= m) {
    if (buf[x + ans] != buf[y + ans + 1 + n]) break;
    ans++;
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", buf + 1, buf + 2 + n);
    buf[n + 1] = '$';
    for (int i = 0; i <= k; i++) {
      for (int j = -k; j <= k; j++) {
        f[i][j + k] = -1;
      }
    }
    f[0][k] = lcp(1, 1);
    for (int i = 1; i <= k; i++) {
      for (int j = -i + 1; j <= i - 1; j++) {
        int x = f[i - 1][j + k] + 1;
        if (x == 0) continue;
        int y = x + j;
        if (x <= n && y <= m) {
          // s[x] -> t[y]
          f[i][j + k] = max(f[i][j + k], x + 1 + lcp(x + 1, y + 1) - 1);
        }
        if (y <= m) {
          // ins before s[x]
          f[i][j + k + 1] = max(f[i][j + k + 1], x + lcp(x, y + 1) - 1);
        }
        if (x <= n) {
          // del s[x]
          f[i][j + k - 1] = max(f[i][j + k - 1], x + 1 + lcp(x + 1, y) - 1);
        }
      }
    }
    int ans = -1;
    for (int i = 0; i <= k; i++) {
      if (f[i][m - n + k] == n) {
        ans = i;
        break;
      }
    }
    if (ans == -1) {
      puts("NO");
    } else {
      puts("YES");
      vector<Ope> plan;
      int last = n, d = m - n;
      for (int i = ans - 1; i >= 0; i--) {
        {
          int x = f[i][d + k] + 1;
          int y = x + d;
          if (x != 0) {
            if (x <= n && 1 <= y && y <= m) {
              if (x + 1 + lcp(x + 1, y + 1) - 1 == last) {
                // replace
                last = f[i][d + k];
                plan.push_back({ 3, y, buf[n + 1 + y] });
                continue;
              }
            }
          }
        }
        {
          int x = f[i][d - 1 + k] + 1;
          int y = x + d - 1;
          if (x != 0) {
            if (y <= m) {
              if (x + lcp(x, y + 1) - 1 == last) {
                // insert
                last = f[i][d - 1 + k];
                d--;
                plan.push_back({ 1, y, buf[n + 1 + y] });
                continue;
              }
            }
          }
        }
        {
          int x = f[i][d + 1 + k] + 1;
          int y = x + d + 1;
          if (x != 0) {
            if (x <= n) {
              if (x + 1 + lcp(x + 1, y) - 1 == last) {
                // del
                last = f[i][d + 1 + k];
                d++;
                plan.push_back({ 2, y });
                continue;
              }
            }
          }
        }
        assert(false);
      }
      reverse(plan.begin(), plan.end());
      printf("%d\n", plan.size());
      for (auto x: plan) {
        if (x.tp == 1) {
          printf("INSERT %d %c\n", x.pos, x.ch);
        } else if (x.tp == 2) {
          printf("DELETE %d\n", x.pos);
        } else if (x.tp == 3) {
          printf("REPLACE %d %c\n", x.pos, x.ch);
        }
      }
    }
  }
  return 0;
}