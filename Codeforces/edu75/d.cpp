#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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

int n; ll s;
PII a[maxn];

int check(ll mid) {
    ll ans = 0, c = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i].first > mid) c++;
        else break;
    }
    assert(c <= n / 2);
    int t = n / 2 + 1 - c;
    for (int i = n; i >= 1; i--) {
        if (a[i].first > mid || a[i].second < mid) ans += a[i].first;
        else {
            if (t) ans += mid, t--;
            else ans += a[i].first;
        }
    }
    if (t) return false;
    return ans <= s;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%I64d", &n, &s);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].first, &a[i].second);
        }
        if (n == 1) {
            printf("%I64d\n", min(s, (ll)a[1].second)); continue;
        }
        sort(a + 1, a + 1 + n);
        ll l = a[n / 2 + 1].first, r = s, ans = l;
        while (l <= r) {
            ll m = (l + r) / 2;
            if (check(m)) ans = m, l = m + 1;
            else r = m - 1;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}