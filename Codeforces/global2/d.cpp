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

int n, q;
ll s[maxn], a[maxn], pre[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%I64d", s + i);
    sort(s + 1, s + 1 + n);
    for (int i = 1; i < n; i++) a[i] = s[i + 1] - s[i];
    sort(a + 1, a + n);
    for (int i = 1; i < n; i++) pre[i] = pre[i - 1] + a[i];

    scanf("%d", &q);
    while (q--) {
        ll l, r; scanf("%I64d%I64d", &l, &r);
        int k = upper_bound(a + 1, a + n, r - l + 1) - a;
        ll ans = pre[k - 1] + (r - l + 1) * (n - k + 1);
        printf("%I64d ", ans);
    }
    return 0;
}