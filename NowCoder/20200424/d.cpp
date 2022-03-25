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
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, p, ten[maxn], cost[300];
char s[maxn];

int main() {
  scanf("%d%d", &n, &p);
  ten[0] = 1;
  for (int i = 1; i < maxn; i++) {
    ten[i] = 10ll * ten[i - 1] % p;
  }
  ms(cost, -1);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    int m = strlen(s), x = 0;
    for (int j = 0; j < m; j++) {
      x = (x * 10 + (s[j] - '0')) % p;
    }
    if (cost[x] == -1 || m < cost[x]) {
      cost[x] = m;
    }
  }
  vector<PII> egs;
  for (int i = 0; i < p; i++) {
    if (cost[i] != -1) {
      egs.emplace_back(cost[i], i);
    }
  }
  while (true) {
    bool flag = false;
    for (int i = 0; i < p; i++) {
      if (cost[i] == -1) continue;
      for (auto& x: egs) {
        int nx = (1ll * i * ten[x.first] + x.second) % p;
        if (cost[nx] == -1 || cost[i] + x.first < cost[nx]) {
          cost[nx] = cost[i] + x.first;
          flag = true;
        }
      }
    }
    if (!flag) break;
  }
  if (cost[0] == -1) puts("-1");
  else printf("%d\n", cost[0]);
  return 0;
}