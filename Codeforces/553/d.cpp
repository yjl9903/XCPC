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

int n, a[maxn], b[maxn];

int main() {
    scanf("%d", &n);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", a + i, b + i);
        ans += 1ll * (n - 1) * a[i]; b[i] -= a[i];
    }
    sort(b + 1, b + 1 + n); reverse(b + 1, b + 1 + n);
    for (int i = 1; i <= n; i++) {
        ans += 1ll * (i - 1) * b[i];
    }
    cout << ans << endl;
    return 0;
}