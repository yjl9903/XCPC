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

int check(int x) {
  if (x % 10 == 9) return 1;
  x /= 10;
  if (x % 10 == 9) return 1;
  x /= 10;
  if (x % 10 == 9) return 1;
  x /= 10;
  if (x % 10 == 9) return 1;
  x /= 10;
  if (x % 10 == 9) return 1;
  return 0;
}

int main() {
  int ans = 0;
  for (int i = 1; i <= 2019; i++) if (check(i)) ans++;
  cout << ans << endl;
  return 0;
}