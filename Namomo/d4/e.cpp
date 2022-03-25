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

int n, f[maxn];
char s[maxn];

int cal(int L, int R) {
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] + 1;
    if (i >= R - L + 1) {
      bool flag = true;
      for (int j = 0; j < R - L + 1; j++) {
        if (s[i - j] != s[R - j]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        f[i] = min(f[i], f[i - (R - L + 1)] + 1);
      }
    }
  }
  return f[n] + R - L + 1;
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  int ans = n;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      ans = min(ans, cal(i, j));
    }
  }
  printf("%d\n", ans);
  return 0;
}