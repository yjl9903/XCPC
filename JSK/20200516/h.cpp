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

int id(char c) {
  if (c == 'A') return 0;
  else if (c == 'T') return 1;
  else if (c == 'G') return 2;
  else if (c == 'C') return 3;
  assert(false);
}

int n, cnt[4][4];
char s[maxn], t[maxn];

int main() {
  scanf("%s%s", s + 1, t + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    cnt[id(s[i])][id(t[i])]++;
  }
  int ans = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < i; j++) {
      int tmp = min(cnt[i][j], cnt[j][i]);
      cnt[i][j] -= tmp;
      cnt[j][i] -= tmp;
      ans += tmp;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        if (i == j || j == k || k == i) continue;
        int tmp = min(cnt[i][j], min(cnt[j][k], cnt[k][i]));
        cnt[i][j] -= tmp;
        cnt[j][k] -= tmp;
        cnt[k][i] -= tmp;
        ans += tmp + tmp;
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        for (int l = 0; l < 4; l++) {
          if (i == j || i == k || i == l || j == k || j == l || k == l) continue;
          int tmp = min(min(cnt[i][j], cnt[j][k]), min(cnt[k][l], cnt[l][i]));
          cnt[i][j] -= tmp;
          cnt[j][k] -= tmp;
          cnt[k][l] -= tmp;
          cnt[l][i] -= tmp;
          ans += tmp + tmp + tmp;
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}