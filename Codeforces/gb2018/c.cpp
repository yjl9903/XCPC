#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll n;

ll cal(ll g) {
    return n / g * (n - g + 2) / 2;
}

int main(){
    cin >> n;
    vector<int> d;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i) continue;
        d.push_back(i);
        if (i != n / i) d.push_back(n / i);
    }
    set<ll> ans;
    for (int& x: d) {
        if (x == n) {
            ans.insert(1); continue;
        }
        ll g = gcd(n, x);
        ans.insert(cal(g));
    }
    for (ll x: ans) printf("%I64d ", x);
    return 0;
}