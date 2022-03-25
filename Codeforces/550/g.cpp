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

int n, a[maxn], vis[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  a[n + 1] = -inf; a[n + 2] = inf;
  vector<int> asc, dsc;
  asc.push_back(n + 1); dsc.push_back(n + 2);
  for (int i = 1; i <= n; i++) {
    bool oka = false, okb = false;
    if (a[i] > a[asc.back()]) {
      oka = true;
    }
    if (a[i] < a[dsc.back()]) {
      okb = true;
    }
    if (!oka && !okb) {
      puts("NO"); return 0;
    } else if (oka && okb) {
      if (i == n) break;
      int nx = a[i + 1];
      if (a[i + 1] > a[i]) {
        asc.push_back(i);
      } else {
        dsc.push_back(i);
        vis[i] = true;
      }
    } else if (oka) {
      asc.push_back(i);
    } else if (okb) {
      dsc.push_back(i);
      vis[i] = true;
    } else {
      assert(false);
    }
  }
  puts("YES");
  for (int i = 1; i <= n; i++) printf("%d ", vis[i]);
  return 0;
}