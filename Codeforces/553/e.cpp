#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= a[i - 1]) {
            ans += 1ll * (n - a[i] + 1) * (a[i] - a[i - 1]);
        } else {
            ans += 1ll * a[i] * (a[i - 1] - a[i]);
        }
    }
    cout << ans;
    return 0;
}