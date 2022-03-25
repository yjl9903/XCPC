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
const int maxn = 1000000 + 5;

char s[maxn];
int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    while (n >= 1 && s[n] == 'a') n--;
    int cnt0 = 0, cnt1 = 0, flag = 1;
    for (int i = 1; i <= n; i++) {
      if (s[i] == 'a') {
        cnt0++;
      } else if (s[i] == 'b') {
        cnt1++;
      }
      if (cnt0 < cnt1) {
        flag = -1; break;
      }
    }
    if (cnt0 > cnt1) {
      flag = 0;
    }
    if (flag == 1) {
      puts("Happy Fang");
    } else if (flag == 0) {
      puts("Sad Fang");
    } else {
      puts("Dead Fang");
    }
  }
  return 0;
}