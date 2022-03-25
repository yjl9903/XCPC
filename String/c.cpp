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
char s[maxn];
bitset<1005> pos[10], ans;

int main() {
  while (scanf("%d", &n) == 1) {
    for (int c = 0; c < 10; c++) pos[c].reset();
    for (int i = 1, k, x; i <= n; i++) {
      scanf("%d", &k);
      while (k--) {
        scanf("%d", &x);
        pos[x].set(i);
      }
    }
    getchar(); gets(s);
    m = strlen(s);
    ans.reset(); ans.set(0);
    for (int i = 0; i < m; i++) {
      ans <<= 1;
      ans &= pos[s[i] - '0'];
      ans.set(0);
      if (ans.test(n)) {
        char tmp = s[i + 1];
        s[i + 1] = 0;
        puts(s + i - n + 1);
        s[i + 1] = tmp;
      }
    }
  }
  return 0;
}