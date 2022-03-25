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

int n, x, deg[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) {
      deg[i] = 0;
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      deg[u]++; deg[v]++;
    }
    if (deg[x] <= 1) {
      puts("Ayush");
    } else {
      if (n % 2 == 1) {
        puts("Ashish");
      } else {
        puts("Ayush");
      }
    }
  }
  return 0;
}