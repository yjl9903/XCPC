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

int n, k, cnt[maxn][26];
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%s", &n, &k, s);
    for (int i = 0; i < k; i++) {
      ms(cnt[i], 0);
    }
    for (int i = 0; i < n; i++) {
      cnt[i % k][s[i] - 'a']++;
    }
    int ans = 0;
    for (int i = 0; i + i + 1 <= k; i++) {
      int sum = 0;
      for (int c = 0; c < 26; c++) {
        if (i + i + 1 < k) {
          cnt[i][c] += cnt[k - i - 1][c];
        }
        sum += cnt[i][c];
      }
      int mx = 0;
      for (int c = 0; c < 26; c++) {
        mx = max(mx, cnt[i][c]);
      }
      ans += sum - mx;
    }
    printf("%d\n", ans);
  }
  return 0;
}