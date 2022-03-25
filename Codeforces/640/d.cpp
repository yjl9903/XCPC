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
    int turn = 1, sa = 0, sb = 0, h = 1, t = n, pre = 0;
    for (; h <= t; turn++) {
      if (turn % 2 == 1) {
        int sum = 0;
        while (h <= t && sum <= pre) {
          sum += a[h++];
        }
        sa += sum;
        pre = sum;
      } else {
        int sum = 0;
        while (h <= t && sum <= pre) {
          sum += a[t--];
        }
        sb += sum;
        pre = sum;
      }
    }
    printf("%d %d %d\n", turn - 1, sa, sb);
  }
  return 0;
}