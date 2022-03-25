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

int n, a[maxn][maxn];

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int sum = 0, r = 0, c = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
      }
      sum += a[i][i];
    }
    for (int i = 1; i <= n; i++) {
      set<int> st;
      for (int j = 1; j <= n; j++) {
        if (st.count(a[i][j])) {
          r++; break;
        }
        st.insert(a[i][j]);
      }
      st.clear();
      for (int j = 1; j <= n; j++) {
        if (st.count(a[j][i])) {
          c++; break;
        }
        st.insert(a[j][i]);
      }
    }
    printf("Case #%d: %d %d %d\n", ++kase, sum, r, c);
  }
  return 0;
}