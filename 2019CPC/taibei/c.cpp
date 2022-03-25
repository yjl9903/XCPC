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

int n, a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  int flag = true;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      for (int k = 1; k < j; k++) {
        if (abs(a[i] - a[j]) % a[k] != 0) {
          flag = false;
        }
        if (abs(a[i] - a[k]) % a[j] != 0) {
          flag = false;
        }
        if (abs(a[j] - a[k]) % a[i] != 0) {
          flag = false;
        }
      }
    }
  }
  puts(flag ? "yes" : "no");
  return 0;
}