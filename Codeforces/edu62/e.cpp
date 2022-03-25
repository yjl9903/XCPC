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
const int maxn = 200000 + 5;

int n, k, a[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 2; i < n; i++) 
        if (a[i - 1] != -1 && a[i + 1] != -1 && a[i - 1] == a[i + 1]) 
            return puts("0"), 0;
    ll ans1 = 1, ans2 = 1;
    for (int i = 1; i <= n; i += 2) {
        if (a[i] != -1) continue;
        ll t = k;
        if (i - 2 >= 1) t--;
        if (i + 2 <= n && a[i + 2] != -1) t--;
        if (t == k - 2) {
            if (a[i - 2] == a[i + 2]) t++;
        }
        ans1 *= t; ans1 %= mod;
    }
    for (int i = 2; i <= n; i += 2) {
        if (a[i] != -1) continue;
        ll t = k;
        if (i - 2 >= 1) t--;
        if (i + 2 <= n && a[i + 2] != -1) t--;
        if (t == k - 2) {
            if (a[i - 2] == a[i + 2]) t++;
        }
        ans2 *= t; ans2 %= mod;
    }
    // cout << ans1 << endl << ans2 << endl;
    cout << ans1 * ans2 % mod << endl;
    return 0;
}