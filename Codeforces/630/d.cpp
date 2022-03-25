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

int k;

int main() {
  scanf("%d", &k);
  puts("3 3");
  int x = k | (1 << 17);
  printf("%d %d %d\n", x, k, x);
  printf("%d %d %d\n", (1 << 17), x, x);
  printf("%d %d %d\n", x, x, k);
  return 0;
}