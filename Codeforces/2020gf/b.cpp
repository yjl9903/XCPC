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

int n, k, a[maxn];

int ceil(int x, int y) {
  return (x + y - 1) / y;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    set<int> st;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      st.insert(a[i]);
    }
    int sz = st.size();
    if (k == 1) {
      puts(sz == 1 ? "1" : "-1");
    } else {
      if (sz <= k) {
        puts("1");
      } else {
        int ans = 1 + ceil(sz - k, k - 1);
        printf("%d\n", ans);
      }
    }
  }
  return 0;
}