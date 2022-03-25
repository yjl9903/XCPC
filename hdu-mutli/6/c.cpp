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

int a, b, c;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &a, &b, &c);
    if ((a + b + c) % 3) {
      puts("-1");
    } else {
      int avg = (a + b + c) / 3;
      int ans = abs(a - avg) + abs(b - avg) + abs(c - avg);
      printf("%d\n", ans / 2 + 1);
    }
  }
  return 0;
}