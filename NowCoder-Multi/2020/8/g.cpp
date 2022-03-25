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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 256 + 1;

int n, a[maxn][4];
char s[200];

int main() {
  map<string, int> mp;
  mp["one"] = 0;
  mp["two"] = 1;
  mp["three"] = 2;
  mp["diamond"] = 0;
  mp["squiggle"] = 1;
  mp["oval"] = 2;
  mp["solid"] = 0;
  mp["striped"] = 1;
  mp["open"] = 2;
  mp["red"] = 0;
  mp["green"] = 1;
  mp["purple"] = 2;
  mp["*"] = -1;

  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%s", s);
      int cur = 0;
      string tot;
      for (int j = 0; s[j]; j++) {
        if (s[j] == '[') {
          tot.clear();
        } else if (s[j] == ']') {
          a[i][cur++] = mp[tot];
        } else {
          tot += s[j];
        }
      }
      // dbg(a[i][0], a[i][1], a[i][2], a[i][3]);
    }
    int ans1 = -1, ans2 = -1, ans3 = -1;
    for (int i = 1; i <= n && ans1 == -1; i++) {
      for (int j = i + 1; j <= n && ans1 == -1; j++) {
        for (int k = j + 1; k <= n && ans1 == -1; k++) {
          if (a[i][0] == -1 || a[j][0] == -1 || a[k][0] == -1
            || (a[i][0] == a[j][0] && a[i][0] == a[k][0])
            || (a[i][0] != a[j][0] && a[i][0] != a[k][0] && a[j][0] != a[k][0])) ;
          else continue;
          if (a[i][1] == -1 || a[j][1] == -1 || a[k][1] == -1
            || (a[i][1] == a[j][1] && a[i][1] == a[k][1])
            || (a[i][1] != a[j][1] && a[i][1] != a[k][1] && a[j][1] != a[k][1])) ;
          else continue;
          if (a[i][2] == -1 || a[j][2] == -1 || a[k][2] == -1
            || (a[i][2] == a[j][2] && a[i][2] == a[k][2])
            || (a[i][2] != a[j][2] && a[i][2] != a[k][2] && a[j][2] != a[k][2])) ;
          else continue;
          if (a[i][3] == -1 || a[j][3] == -1 || a[k][3] == -1
            || (a[i][3] == a[j][3] && a[i][3] == a[k][3])
            || (a[i][3] != a[j][3] && a[i][3] != a[k][3] && a[j][3] != a[k][3])) ;
          else continue;
          ans1 = i;
          ans2 = j;
          ans3 = k;
        }
      }
    }
    printf("Case #%d: ", ++kase);
    if (ans1 == -1) {
      puts("-1");
    } else {
      printf("%d %d %d\n", ans1, ans2, ans3);
    }
  }
  return 0;
}