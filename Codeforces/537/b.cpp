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

int n, k, m, a[maxn];

int main(){
    scanf("%d%d%d", &n, &k, &m);
    ll sum = 0;
    for (int i = 0; i < n; i++) scanf("%d", a + i), sum += a[i];
    sort(a, a + n);
    ll pre = 0; double ans = 0;
    for (int i = 0; i < n && i <= m; i++) {
        ll t = sum - pre;
        // cout << t << ' ';
        if (m - i <= 1ll * k * (n - i)) t += m - i;
        else t += 1ll * k * (n - i);
        // cout << t << endl;
        ans = max(ans, (double)t / (double)(n - i));
        pre += a[i];
    }
    printf("%.10lf\n", ans);
    return 0;
}