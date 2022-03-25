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

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    ll ans = 0; int last = a[n] + 1;
    for (int i = n; i >= 1; i--) {
        if (last == 1) break;
        ans += min(last - 1, a[i]);
        last = min(last - 1, a[i]);
    }
    cout << ans << endl;
    return 0;
}