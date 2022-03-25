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



int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    if (n > 0) {
      while (k--) {
        n = (n + 1) / 2;
        if (n == 1) break;
      }
    }
    printf("%d\n", n);
  }  
  return 0;
}