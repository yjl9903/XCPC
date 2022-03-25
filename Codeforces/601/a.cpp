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
const int maxn = 500 + 5;

char gc(int x) {
  if (x < 26) return x + 'a';
  else if (x < 52) return x - 26 + 'A';
  else return x - 52 + '0';
  return '.';
}

int r, c, k;
char s[maxn][maxn], ans[maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &r, &c, &k);
    int sum = 0;
    for (int i = 1; i <= r; i++) {
      scanf("%s", s[i] + 1);
      for (int j = 1; j <= c; j++) {
        if (s[i][j] == 'R') sum++;
        ans[i][j] = 0;
      }
    }
    vector<int> num(k, sum / k);
    for (int i = sum / k * k + 1, j = 0; i <= sum; i++, j++) {
      num[j]++;
    }
    int p = 0;
    for (int i = 1; i <= r; i++) {
      if (i % 2 == 1) {
        for (int j = 1; j <= c; j++) {
          ans[i][j] = gc(p);
          if (s[i][j] == 'R') num[p]--;
          if (p + 1 < k && num[p] == 0) p++;
        }
      } else {
        for (int j = c; j >= 1; j--) {
          ans[i][j] = gc(p);
          if (s[i][j] == 'R') num[p]--;
          if (p + 1 < k && num[p] == 0) p++;
        }
      }
    }
    for (int i = 1; i <= r; i++) {
      for (int j = 1; j <= c; j++) {
        putchar(ans[i][j]);
      }
      puts("");
    }
  }
  return 0;
}