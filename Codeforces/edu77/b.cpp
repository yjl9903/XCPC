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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int a, b;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &a, &b);
    if ((2 * b - a) % 3 == 0 && (2 * a - b) % 3 == 0 && 2 * b >= a && 2 * a >= b) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}