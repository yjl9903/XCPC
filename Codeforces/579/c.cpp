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
const int maxn = 2000000 + 5;

int n;
ll a, g;

int main() {
    scanf("%d%I64d", &n, &g);
    for (int i = 2; i <= n; i++) scanf("%I64d", &a), g = __gcd(g, a);
    ll ans = 0;
    for (ll i = 1; i * i <= g; i++) {
        if (g % i) continue;
        ans++;
        if (i * i != g) ans++;
    }
    cout << ans;
    return 0;
}