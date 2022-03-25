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
const int maxn = 2000 + 5;

int n, m;
char mp[maxn][maxn];

int main() {
  scanf("%d%d", &n, &m);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%s", mp[i] + 1);
    int cnt = 0;
    for (int j = 1; j < m; j++) {
      cnt += mp[i][j] == '0';
    }
    for (int j = m; j <= n; j++) {
      cnt += mp[i][j] == '0';
      if (cnt == m) ans++;
      cnt -= mp[i][j - m + 1] == '0';
    }
  }
  printf("%d\n", ans);
  return 0;
}