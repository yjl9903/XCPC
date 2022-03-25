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
#include <bitset>
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
const int maxn = 5000000 + 5;

int n, m;
vector<int> rg[1005];
char s[maxn];
bitset<maxn> pos[10], ans, tmp;

int main() {
  while (scanf("%d", &n) == 1) {
    for (int i = 1, k, x; i <= n; i++) {
      scanf("%d", &k); rg[i].clear();
      while (k--) {
        scanf("%d", &x); rg[i].push_back(x);
      }
    }
    getchar(); gets(s);
    m = strlen(s);
    for (int c = 0; c < 10; c++) {
      pos[c].reset();
    }
    for (int i = 0; i < m; i++) {
      pos[s[i] - '0'].set(i);
      ans.set(i);
    }
    for (int i = 1; i <= n; i++) {
      tmp.reset();
      for (auto& ch: rg[i]) {
        tmp |= pos[ch];
      }
      ans &= tmp;
      ans <<= 1;
    }
    for (int i = 1; i <= m; i++) {
      if (!ans.test(i)) continue;
      char tmp = s[i];
      s[i] = 0;
      puts(s + i - n);
      s[i] = tmp;
    }
  }
  return 0;
}