#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r % mod;
}

int n, a[maxn];
map<int,PII> mp;

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        if (mp.count(a[i])) {
            mp[a[i]].second = i;
        } else {
            mp[a[i]].first = mp[a[i]].second = i;
        }
    }
    vector<PII> v;
    for (auto& x: mp) {
        v.push_back({x.second.first, x.second.second});
    }
    sort(v.begin(), v.end());
    int l = v[0].first, r = v[0].second, cnt = v[0].first - 1;
    for (int i = 1; i < v.size(); i++) {
        if (v[i].first <= r) {
            r = max(r, v[i].second);
        } else {
            cnt += v[i].first - r;
            l = v[i].first; 
            r = v[i].second;
        }
    }
    cnt += n - r;
    cout << qpow(2ll, cnt);
    return 0;
}