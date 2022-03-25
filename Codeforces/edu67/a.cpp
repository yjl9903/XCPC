#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ll n, s, t;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        cin >> n >> s >> t;
        ll ans = 0;
        ll a = s, b = t, c = s + t - n;
        a -= c; b -= c;
        if (a > 0) ans = a + 1;
        if (b > 0) ans = max(b + 1, ans);
        ans = max(ans, 1ll);
        cout << ans << '\n';
    }
    return 0;
}