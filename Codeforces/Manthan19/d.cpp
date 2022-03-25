#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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
const int maxn = 200000 + 5;

int n, p[maxn];
ll s[maxn];

struct BIT {
    ll a[maxn];
    inline int lowbit(int x) { return x & -x; }
    void insert(int i, int x) {
        for (; i <= n; i += lowbit(i)) a[i] += x;
    }
    ll query(int i) {
        ll r = 0;
        for (; i; i -= lowbit(i)) r += a[i];
        return r;
    }
} f;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%I64d", s + i);
    for (int i = 1; i <= n; i++) f.insert(i, i);
    for (int i = n; i >= 1; i--) {
        int l = 0, r = n, ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (f.query(m) <= s[i]) ans = m + 1, l = m + 1;
            else r = m - 1;
        }
        dbg(ans);
        assert(ans != -1);
        f.insert(ans, -ans);
        p[i] = ans;
        // int x = f.findx(s[i] + 1);
        // p[i] = x;
        // f.insert(x, -1);
    }
    for (int i = 1; i <= n; i++) printf("%d ", p[i]);
    return 0;
}