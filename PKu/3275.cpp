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
#include <bitset>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

int n, m, G[maxn][maxn];
bitset<maxn> mp[maxn];

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 1; i <= m; i++) {
      int u, v; scanf("%d%d", &u, &v);
      mp[u].set(v);
    }
    for (int k = 1; k <= n; k++) {
      for (int i = 1; i <= n; i++) {
        if (mp[i].test(k)) {
          mp[i] |= mp[k];
        }
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        if (!mp[i].test(j) && !mp[j].test(i)) {
          ans++;
        }
      }
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) {
      mp[i].reset();
    }
  }
  
  return 0;
}