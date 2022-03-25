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

int n; char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  int c1 = 0, c6 = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '1') c1++;
    if (s[i] == '6') c6++;
  }
  cout << min(c6 - 1, c1);
  return 0;
}