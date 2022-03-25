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
int n, key[300];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  key['a'] = key['e'] = key['i'] = key['o'] = key['u'] = 1;
  int cnt = 0;
  for (int i = 1, j; i <= n; i = j) {
    j = i;
    while (j <= n && key[s[i]] == key[s[j]]) j++;
    cnt++;
  }
  if (cnt == 4) puts("yes");
  else puts("no");
  return 0;
}