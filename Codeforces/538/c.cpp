#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

ll n, b;
map<ll,int> mp;

int main() {
    cin >> n >> b;
    for (ll i = 2; i * i <= b; i++) {
        if (b % i) continue;
        int c = 0;
        while (b % i == 0) b /= i, c++;
        mp[i] = c;
    }
    if (b > 1) mp[b] = 1;
    ll ans = 1e18;
    for (auto& x: mp) {
        ll d = x.first;
        ll c = 0;
        for (ll i = 1; d <= n; d *= x.first) {
            c += n / d;
            if (n / d < x.first) break;
        }
        ans = min(ans, c / x.second);
        // cout << x.first << ' ' << c << endl;
    }
    cout << ans << endl;
    return 0;
}