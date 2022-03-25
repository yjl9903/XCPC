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

int n; ll s, suml;
PII a[maxn];

int check(ll mid) {
    // ll sum = suml;
    // for (int i = n / 2 + 1; i <= n; i++) {
    //     if (mid > a[i].second) return false;
    //     if (a[i].first >= mid) sum += a[i].first;
    //     else sum += mid;
    // }
    // dbg(mid, sum);
    // return sum <= s;
    ll ans = 0; int p = -1;
    vector<int> le, ri;
    for (int i = 1; i <= n; i++) {
        if (a[i].first <= mid && mid <= a[i].second) {
            if (p == -1) p = i;
            else {
                if (a[i].second < a[p].second) p = i;
            }
        }
    }
    if (p == -1) return 0;

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
            printf("%lld\n", min(s, (ll)a[1].second)); continue;
        }
        // sort(a + 1, a + 1 + n);
        ll l = 1, r = s, ans = l;
        while (l <= r) {
            ll m = (l + r) / 2;
            if (check(m)) ans = m, l = m + 1;
            else r = m - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}