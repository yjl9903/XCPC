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

int n, fail[maxn];
char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  bool flag = true;
  for (int i = 2; i <= n; i++) {
    int cur = fail[i - 1];
    while (cur && s[cur + 1] != s[i]) cur = fail[cur];
    if (s[cur + 1] == s[i]) cur++;
    fail[i] = cur;
    if (fail[i] != 0) flag = false;
  }
  if (flag) {
    puts("Correct");
  } else {
    puts("Wrong Answer");
  }
  return 0;
}