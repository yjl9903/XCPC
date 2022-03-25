#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, l;
ll c[maxn], a[maxn];

int main() {
    scanf("%d%d", &n, &l);
    for (int i = 0; i < n; i++) scanf("%I64d", c + i);
    a[0] = c[0];
    for (int i = 1; i <= 30; i++) {
        if (c[i] == 0) a[i] = a[i - 1] + a[i - 1];
        else a[i] = min(c[i], a[i - 1] + a[i - 1]);
    }
    for (int i = 29; i >= 0; i--) a[i] = min(a[i], a[i + 1]);
    ll ans = 1ll << 62, tot = 0; int flag = 1;
    for (int i = 30; i >= 0; i--) {
        if (l & (1 << i)) {
            flag = 0;
            tot += a[i];
        } else if (flag) {
            ans = min(ans, a[i]);
        } else {
            ans = min(ans, tot + a[i]);
        }
    }
    cout << min(ans, tot) << endl;
    return 0;
}