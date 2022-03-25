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
#include <ctime>
#include <random>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, m, cost[maxn], val[maxn];
ll f[maxn], g[maxn];

ll solve(int mod) {
  f[0] = g[0] = 0;
  for (int i = 1; i < mod; i++) f[i] = g[i] = -inf;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < mod; j++) {
      g[j] = max(f[j], f[(j + mod - cost[i]) % mod] + val[i]);
    }
    for (int i = 0; i < mod; i++) {
      f[i] = g[i];
    }
  }
  for (int i = n + 1; i <= n + m; i++) {
    for (int j = 0; j < mod; j++) {
      g[j] = max(f[j], f[(j + cost[i]) % mod] + val[i]);
    }
    for (int i = 0; i < mod; i++) {
      f[i] = g[i];
    }
  }
  return f[0];
}

mt19937 rnd(time(nullptr));

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + m; i++) {
      scanf("%d%d", cost + i, val + i);
    }

    
  }
  return 0;
}