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
const int maxn = 200 + 5;

int n;
bool vis[maxn][maxn];

int main() {
  scanf("%d", &n);
  bool flag = true;
  for (int i = 1; i <= n; i++) {
    int d, l, r, c;
    scanf("%d%d%d%d", &d, &l, &r, &c);
    if (d == 0) {
      for (int j = c; j <= c + l - 1; j++) {
        if (j > 10) flag = false;
        if (vis[r][j]) flag = false;
        vis[r][j] = true;
      }
    } else {
      for (int i = r; i <= r + l - 1; i++) {
        if (i > 10) flag = false;
        if (vis[i][c]) flag = false;
        vis[i][c] = true;
      }
    }
  }
  puts(flag ? "Y" : "N");
  return 0;
}