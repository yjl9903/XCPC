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

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int mx = a[1], ans = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(a[i], mx);
        if (mx == i) ans++;
        // if (mx == i) return printf("%d", i), 0;
    }
    cout << ans << endl;
    return 0;
}