#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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

int key[maxn];

int cal(int x) {
    int ans = 0;
    while (x) {
        ans += x % 10; x /= 10;
    }
    return ans;
}

int main() {
    // for (int i = 1; i < maxn; i++) {
    //     key[i] = (cal(i) == i / 2);
    //     if (key[i]) dbg(i, key[i]);
    // }
    int T; scanf("%d", &T);
    while (T--) {
        ll n; scanf("%lld", &n);
        int ans = 0;
        if (n % 17 == 0) ans++;
        if (n % 18 == 0) ans++;
        printf("%d\n", ans);
    }
    return 0;
}