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

ll n, m;
int q;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    ll g = __gcd(n, m);
    ll nt = n / g, mt = m / g;
    dbg(nt, mt);
    int sx, ex; ll sy, ey;
    while (q--) {
        cin >> sx >> sy >> ex >> ey;
        sy--, ey--;
        ll b1, b2;
        if (sx == 1) b1 = sy / nt;
        else b1 = sy / mt;
        if (ex == 1) b2 = ey / nt;
        else b2 = ey / mt;
        dbg(b1, b2);
        if (b1 == b2) puts("YES");
        else puts("NO");
    }
    return 0;
}