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

const char Pic[21][51] = {
  "...........................,]]OOO@@@@OOO]`........",
  "....................,]OO@@@@@@@@@@@@@@@@@@@@O`....",
  "................./O@@@@@@@@@@@@@@@@@@@@@@@@@@@@^..",
  "............../O@@@@@@@@@@@@@@@OOOOOOO@@@@@@@@@@@.",
  "..........,/@@@@@@@@@@@@O/[.............[O@@@@@@@\\",
  "........,O@@@@@@@@@@O/`..................,O@@@@@@O",
  ".......O@@@@@@@@@O`......]OO@@@O\\`........O@@@@@@@",
  ".....,O@@@@@@@@/`.....]O@@@@@@@@@@^.......O@@@@@@@",
  "...,/@@@@@@@O/...../@@@@@@@@@@@@@@O....../@@@@@@@0",
  "..=@@@@@@@O`...../@@@@@@@@@@@@@@@@^.....O@@@@@@@O.",
  "./@@@@@@@/......O@@@@@@@@@@@@@@@O`..../@@@@@@@@O..",
  "=@@@@@@@O......O@@@@@@@@@@@@@@@^....O@@@@@@@@@O...",
  "O@@@@@@@^.....=@@@@@@@@@@@@@O[..../@@@@@@@@@O`....",
  "@@@@@@@O.......\\@@@@@@@@O[...../O@@@@@@@@@O`......",
  "@@@@@@@@^.........[`.......]OO@@@@@@@@@@O`........",
  "O@@@@@@@@O\\............]/@@@@@@@@@@@@O/...........",
  "=@@@@@@@OOOoo`........O@@@@@@@@@@@@/`.............",
  "..\\OOOOO*,`*..........O@@@@@@@@@O`................",
  ".....,[[..............O@@@@@@O`...................",
  "......................O@@@@@@O....................",
};

int n, h, w;
char ans[maxn][maxn];

int main() {
  scanf("%d%d%d", &n, &h, &w);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      ans[i][j] = '.';
    }
  }
  auto check = [&](int x, int y) {
    return x < 0 || y < 0 || x >= h || y >= w;
  };
  for (int i = 1, x, y, r; i <= n; i++) {
    scanf("%d%d%d", &x, &y, &r);
    if (r == 0) {
      for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 50; j++) {
          if (Pic[i][j] == '.') continue;
          if (check(i + x, j + y)) continue;
          ans[i + x][j + y] = Pic[i][j];
        }
      }
    } else if (r == 1) {
      for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 50; j++) {
          if (Pic[i][j] == '.') continue;
          if (check(19 - i + x, 49 - j + y)) continue;
          ans[19 - i + x][49 - j + y] = Pic[i][j];
        }
      }
    }
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      putchar(ans[i][j]);
    }
    puts("");
  }
  return 0;
}