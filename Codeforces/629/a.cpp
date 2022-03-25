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

int a, b;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &a, &b);
    int k = (a + b - 1) / b;
    printf("%I64d\n", 1ll * b * k - a);
  }
  return 0;
}