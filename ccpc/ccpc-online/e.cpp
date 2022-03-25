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

char s[maxn];
int n, cnt[30];

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    ms(cnt, 0);
    for (int i = 1; s[i]; i++) {
      cnt[s[i] - 'a']++;
    }
    int ans = 1;
    for (int i = 0; i < 26; i++) ans = max(ans, cnt[i]);
    printf("Case #%d: %d\n", ++kase, ans);
  }
  return 0;
}