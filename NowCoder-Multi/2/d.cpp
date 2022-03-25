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

void work(int a, int b) {
  if (a > b) puts("first");
  else if (a < b) puts("second");
  else puts("tie");
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int a1, b1, a2, b2;
    scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
    if (a1 > b1) swap(a1, b1);
    if (a2 > b2) swap(a2, b2);
    if (a1 == 2 && b1 == 8 && a2 == 2 && b2 == 8) {
      puts("tie");
    } else if (a1 == 2 && b1 == 8) {
      puts("first");
    } else if (a2 == 2 && b2 == 8) {
      puts("second");
    } else if (a1 == b1 && a2 == b2) {
      work(a1, a2);
    } else if (a1 == b1) {
      puts("first");
    } else if (a2 == b2) {
      puts("second");
    } else if ((a1 + b1) % 10 != (a2 + b2) % 10) {
      work((a1 + b1) % 10, (a2 + b2) % 10);
    } else {
      work(b1, b2);
    }
  }
  return 0;
}