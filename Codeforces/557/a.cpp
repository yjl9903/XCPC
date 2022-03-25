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

int n, h, m, a[maxn];

int main() {
    scanf("%d%d%d", &n, &h, &m);
    for (int i = 1; i <= n; i++) a[i] = h;
    for (int i = 1, l, r, h; i <= m; i++) {
        scanf("%d%d%d", &l, &r, &h);
        for (int j = l; j <= r; j++) a[j] = min(a[j], h);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += a[i] * a[i];
    cout << ans;
    return 0;
}