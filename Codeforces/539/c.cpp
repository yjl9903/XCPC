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
const int maxn = 300000 + 5;

int n, a[maxn], pre[maxn];
map<int,int> mp[2];

int main() {
    scanf("%d", &n); mp[0][0]++;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        pre[i] = pre[i - 1] ^ a[i];
        mp[i % 2][pre[i]]++;
    }
    // for (int i = 1; i <= n; i++) cout << pre[i] << ' '; cout << endl;
    ll ans = 0;
    for (auto& x: mp[0]) {
        ans += 1ll * x.second * (x.second - 1) / 2;
    }
    for (auto& x: mp[1]) {
        ans += 1ll * x.second * (x.second - 1) / 2;
    }
    cout << ans << endl;
    return 0;
}