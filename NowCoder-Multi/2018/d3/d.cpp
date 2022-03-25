#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn], mn = 1 << 30;;
ll ans = 0;

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i), ans += a[i], mn = min(a[i], mn);
    printf("%lld\n", ans + 1ll * mn * (n - 2));
    return 0;
}