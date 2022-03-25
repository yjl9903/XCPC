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
const int maxn = 500 + 5;

int n, cur, p[maxn], mp[maxn][maxn];

const vector<PII> dir = {
  { 0, -1 }, { 1, 0 }
};

void dfs(int& c, int x, int y) {
  mp[x][y] = cur;
  c--;
  if (c == 0) return ;
  for (auto& d: dir) {
    int tx = x + d.first;
    int ty = y + d.second;
    if (tx < 1 || tx > n) continue;
    if (ty < 1 || ty > tx) continue;
    if (mp[tx][ty] != -1) continue;
    dfs(c, tx, ty);
    if (c == 0) return ;
  }
}

int main() {
  ms(mp, -1);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", p + i);
    int x = p[i];
    cur = p[i];
    dfs(x, i, i);
    assert(x == 0);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      assert(mp[i][j] != -1);
      printf("%d%c", mp[i][j], " \n"[j == i]);
    }
  }
  return 0;
}