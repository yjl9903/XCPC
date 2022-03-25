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

char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int cnt0 = 0, cnt2 = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
      if (s[i] == '0') cnt0++;
      if ((s[i] - '0') % 2 == 0) cnt2++;
      sum += s[i] - '0';
    }
    if (sum == 0) {
      puts("red"); continue;
    }
    if (sum % 3 || !cnt0 || !(cnt2 - 1)) {
      puts("cyan"); continue;
    }
    puts("red");
  }
  return 0;
}