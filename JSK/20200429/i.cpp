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

int w, s, c, k;

int main() {
  cin >> w >> s >> c >> k;
  if (k == 0) {
    puts("NO");
    return 0;
  }
  if (k > s) {
    puts("YES");
  } else if (k == s) {
    if (k + k >= w + c) {
      puts("YES");
    } else {
      puts("NO");
    }
  } else {
    if (k > w + c) {
      puts("YES");
    } else if (k == w + c && k + k >= s) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}