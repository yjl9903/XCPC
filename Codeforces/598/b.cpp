#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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
const int maxn = 100000 + 5;

int n, a[maxn], pos[maxn], vis[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      pos[a[i]] = i; vis[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      int x = pos[i];
      while (x > 1 && !vis[x - 1] && i < a[x - 1]) {
        x--; vis[x] = 1;
      }
      for (int j = pos[i]; j >= x + 1; j--) {
        a[j] = a[j - 1];
        pos[a[j]] = j;
      }
      pos[i] = x; a[x] = i;
    }
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    puts("");
  }
  return 0;
}