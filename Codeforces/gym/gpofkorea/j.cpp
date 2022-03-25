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
const int maxn = 300000 + 5;

const char S[] = "UDLR";

int n, q, preX[maxn], preY[maxn], nxt[maxn];
char cmd[maxn];
PII dst[maxn];

PII getC(char c) {
  if (c == 'L') {
    return { 1, 0 };
  } else if (c == 'R') {
    return { -1, 0 };
  } else if (c == 'U') {
    return { 0, -1 };
  } else if (c == 'D') {
    return { 0, 1 };
  } else {
    assert(false);
  }
}

int main() {
  scanf("%d%s%d", &n, cmd + 1, &q);
  for (int i = 1; i <= n; i++) {
    preX[i] = preX[i - 1];
    preY[i] = preY[i - 1];
    if (cmd[i] == 'U') preY[i]++;
    if (cmd[i] == 'D') preY[i]--;
    if (cmd[i] == 'L') preX[i]--;
    if (cmd[i] == 'R') preX[i]++;
  }
  map<PII, int> last[4];
  map<PII, PII> key;
  for (int i = n; i >= 1; i--) {
    if (cmd[i] == cmd[i + 1]) {
      dst[i] = dst[i + 1];
    } else {
      PII cur = getC(cmd[i]);
      if (i == n) {
        dst[i] = cur;
      } else {
        int nx = n + 1;
        dst[i] = { cur.first + preX[n] - preX[i], cur.second + preY[n] - preY[i] };
        for (int j = 0; j < 4; j++) {
          auto t = getC(S[j]);
          int tx = preX[i] - cur.first + t.first;
          int ty = preY[i] - cur.second + t.second;
          if (last[j].count({ tx, ty })) {
            int R = last[j][{ tx, ty }];
            if (R < nx) {
              nx = R;
              dst[i] = dst[R];
            }
          }
        }
      }
    }
    {
      PII cur { preX[i - 1], preY[i - 1] };
      if (cmd[i] == 'U') last[0][cur] = i;
      if (cmd[i] == 'D') last[1][cur] = i;
      if (cmd[i] == 'L') last[2][cur] = i;
      if (cmd[i] == 'R') last[3][cur] = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    auto cur = getC(cmd[i]);
    cur.first -= preX[i - 1];
    cur.second -= preY[i - 1];
    if (key.count(cur)) continue;
    key[cur] = dst[i];
  }
  while (q--) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (key.count({ x, y })) {
      auto dst = key[{ x, y }];
      printf("%d %d\n", dst.first, dst.second);
    } else {
      x += preX[n];
      y += preY[n];
      printf("%d %d\n", x, y);
    }
  }
  return 0;
}