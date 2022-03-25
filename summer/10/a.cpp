#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, p, k, a[maxn];
map<int,int> mp;

ll q(int x) {
    return 1ll * x * x % p * x % p * x % p;
}

int main() {
    scanf("%d%d%d", &n, &p, &k);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        int tot = ((q(a[i]) + p - 1ll * k * a[i] % p) % p + p) % p;
        ans += mp[tot];
        mp[tot]++;
    }
    cout << ans;
    return 0;
}