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

int n, q;
char s[maxn];
vector<int> pos[26];

int main() {
  scanf("%s%d", s + 1, &q);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    pos[s[i] - 'a'].push_back(i);
  }
  while (q--) {
    int l, r; scanf("%d%d", &l, &r);
    if (l == r) {
      puts("Yes");
      continue;
    }
    int sum = 0;
    for (int c = 0; c < 26; c++) {
      int tot = upper_bound(begin(pos[c]), end(pos[c]), r) - lower_bound(begin(pos[c]), end(pos[c]), l);
      if (tot > 0) {
        sum++;
      }
    }
    if (sum == 1) {
      puts("No");
    } else if (sum > 2) {
      puts("Yes");
    } else {
      if (s[l] != s[r]) {
        puts("Yes");
      } else {
        puts("No");
      }
    }
  }
  return 0;
}