#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn], q[maxn * 2];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    ll ans = 0; set<int> st;
    int l = 1, r = 1; a[n + 1] = n + 1;
    for (int i = 1; i <= n; i++) {
        while (l + 1 <= r && a[q[l]] > a[i]) {
            l++;
        }
        if (a[i] > a[i - 1]) {
            if (a[i] < a[i + 1]) {
                int p = 0; if (q[l] > 1) p = a[q[l] - 1];
                ans += max(1ll * (a[q[l]] - p + 1) * (a[i + 1] - a[i] + 1), 0ll);
            }
            q[++r] = i;
        }
    }
    cout << ans << endl;
    return 0;
}