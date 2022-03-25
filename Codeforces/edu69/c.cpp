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
const ll inf = 1ll << 50;
const int maxn = 300000 + 5;

int n, k, a[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    ll ans = 0;
    vector<ll> v;
    for (int i = 2; i <= n; i++) v.push_back(-a[i] + a[i - 1]);
    v.push_back(-a[1] - inf); v.push_back(a[n] - inf);
    sort(v.begin(), v.end());
    for (int i = 0; i < k + 1; i++) ans += v[i];
    cout << ans + 2 * inf;
    return 0;
}