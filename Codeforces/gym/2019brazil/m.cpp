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

int n, c, t, a[maxn];

int check(int x) {
    ll mx = 1ll * x * t;
    int cnt = 0;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > mx) return 0;
        if (sum + a[i] > mx) {
            cnt++; sum = a[i];
        } else {
            sum += a[i];
        }
    }
    if (sum) cnt++;
    return cnt <= c;
}

int main() {
    scanf("%d%d%d", &n, &c, &t);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int l = 1, r = inf, ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) r = m - 1, ans = m;
        else l = m + 1;
    }
    printf("%d\n", ans);
    return 0;
}