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

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    sort(a + 1, a + 1 + n, greater<int>());
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        assert(i - a[i] != j - a[j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      printf("%d ", a[i]);
    }
    puts("");
  }
  return 0;
}