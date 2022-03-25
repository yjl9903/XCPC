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

int n, vis[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      vis[i] = 0;
    }
    vector<int> v;
    for (int i = 1, k; i <= n; i++) {
      scanf("%d", &k);
      int ans = -1, x;
      while (k--) {
        scanf("%d", &x);
        if (ans == -1 && !vis[x]) {
          ans = x; vis[x] = 1;
        }
      }
      if (ans == -1) {
        v.push_back(i);
      }
    }
    if (v.empty()) {
      puts("OPTIMAL");
    } else {
      vector<int> v2;
      for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
          v2.push_back(i);
        }
      }
      assert(v.size() == v2.size());
      puts("IMPROVE");
      printf("%d %d\n", v[0], v2[0]);
    }
  }
  return 0;
}