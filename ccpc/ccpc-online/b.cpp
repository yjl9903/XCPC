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
const int maxn = 2000 + 5;

int n, a[maxn][maxn], k[10][10];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
      }
    }
    int sum = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        scanf("%d", &k[i][j]);
        sum += k[i][j];
      }
    }
    if (sum == k[0][0]) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          printf("%d%c", a[i][j], " \n"[j == n]);
        }
      }
    } else {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          printf("0%c", " \n"[j == n]);
        }
      }
    }
  }
  return 0;
}