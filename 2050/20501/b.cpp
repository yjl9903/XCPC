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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n;
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
} 

int main() {
    scanf("%d", &n);
    ll ans = 0;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        ll t = 1ll * (n - i + 1) * (n - i + 2) / 2;
        add(ans, 1ll * x * i % mod * t % mod);
    }
    cout << ans << endl;
    return 0;
}