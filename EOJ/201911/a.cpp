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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, m, k; ll x;
char s[maxn], chs[30];
string choose[maxn];

int main() {
  scanf("%d%d%d%lld%s", &n, &m, &k, &x, s + 1);
  for (int i = 1; i <= m; i++) {
    scanf("%s", chs);
    choose[i] = string(chs);
    sort(choose[i].begin(), choose[i].end());
  }
  string ans;
  x--;
  for (int i = m; i >= 1; i--) {
    ans.push_back(choose[i][x % k]);
    x /= k;
  }
  reverse(ans.begin(), ans.end());
  int p = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '#') {
      s[i] = ans[p++];
    }
  }
  cout << s + 1;
  return 0;
}