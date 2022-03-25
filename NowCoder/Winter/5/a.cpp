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
const int maxn = 100000 + 5;

char s[maxn], t[maxn];
int n, m;

int main() {
  scanf("%d%d%s%s", &n, &m, s + 1, t + 1);
  int ans = abs(n - m);
  for (int i = 1; i <= min(n, m); i++) {
    if (s[i] != t[i]) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}