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
const int maxn = 200000 + 5;

int n, dp[maxn][4];
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      if (i > 2 && i + 2 <= n && s[i - 2] == 't' && s[i - 1] == 'w' && s[i] == 'o' && s[i + 1] == 'n' && s[i + 2] == 'e') {
        s[i] = 0; ans.push_back(i);
      }
    }
    for (int i = 2; i < n; i++) {
      if (s[i - 1] == 't' && s[i] == 'w' && s[i + 1] == 'o') {
        s[i] = 0; ans.push_back(i);
      } else if (s[i - 1] == 'o' && s[i] == 'n' && s[i + 1] == 'e') {
        s[i] = 0; ans.push_back(i);
      }
    }
    printf("%d\n", (int)ans.size());
    for (int x: ans) printf("%d ", x);
    puts("");
  }
  return 0;
}