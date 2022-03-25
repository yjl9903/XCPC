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

int n;
char a[maxn], b[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s%s", &n, a + 1, b + 1);
    int red = 0, blue = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] > b[i]) {
        red++;
      } else if (a[i] < b[i]) {
        blue++;
      }
    }
    if (red > blue) {
      puts("RED");
    } else if (red < blue) {
      puts("BLUE");
    } else {
      puts("EQUAL");
    }
  }
  return 0;
}