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

ll x, a, y, b;

int main() {
    while (cin >> x >> a >> y >> b) {
        ll g1 = __gcd(x, a);
        x /= g1; a /= g1;
        ll g2 = __gcd(y, b);
        y /= g2; b /= g2;
        __int128 f = x;
        f *= b;
        __int128 g = y;
        g *= a;
        if (f - g > 0) puts(">");
        else if (f - g < 0) puts("<");
        else puts("=");
    }
    return 0;
}