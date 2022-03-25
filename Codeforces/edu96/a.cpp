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

int main() {
  f[0] = true;
  for (int i = 1; i <= 1000; i++) {
    if (i >= 3) f[i] |= f[i - 3]; 
    if (i >= 5) f[i] |= f[i - 5]; 
    if (i >= 7) f[i] |= f[i - 7]; 
  }
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    if (f[n]) {
      int sum[3] = { 0, 0, 0 };
      while (n) {
        if (n >= 3 && f[n - 3]) {
          n -= 3;
          sum[0]++;
        } else if (n >= 5 && f[n - 5]) {
          n -= 5;
          sum[1]++;
        } else if (n >= 7 && f[n - 7]) {
          n -= 7;
          sum[2]++;
        }
      }
      printf("%d %d %d\n", sum[0], sum[1], sum[2]);
    } else {
      puts("-1");
    }
  }
  return 0;
}