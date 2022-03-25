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

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    vector<int> ans;
    int tot = 1;
    while (n) {
      if (tot * (n % 10)) {
        ans.push_back(tot * (n % 10));
      }
      n /= 10; tot *= 10;
    }
    printf("%d\n", ans.size());
    for (int x: ans) printf("%d ", x);
    puts("");
  }
  return 0;
}