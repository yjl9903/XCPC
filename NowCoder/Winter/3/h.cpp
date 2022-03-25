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
const int maxn = 100000 + 5;

namespace sieve{
    const int maxp = 1000000 + 5;
    int vis[maxp], prime[maxp], tot;
    void init() {
        ms(vis, 0);
        for (int i = 2; i < maxp; i++) {
            if (!vis[i]) prime[tot++] = i;
            for (int j = 0; j < tot && prime[j] * i < maxp; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) break;
            }
        }
    }
}
using namespace sieve;

int n, m;
vector<int> pos[maxn];

int main() {
  sieve::init();
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    int cnt = 0;
    for (int j = 1; 1ll * j * j <= i; j++) {
      if (i % j) continue;
      if (j > 1 && vis[j]) cnt++;
      if (1ll * j * j != i && vis[i / j]) cnt++;
    }
    pos[cnt].push_back(i);
    // cout << i << ' ' << cnt << endl;
  }
  while (m--) {
    int k; scanf("%d", &k);
    printf("%d\n", pos[k].size());
  }
  return 0;
}