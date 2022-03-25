#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const ll mod = 998244353;

int n; char s[maxn];

int main(){
    scanf("%d%s", &n, s);
    int flag = 1;
    for (int i = 0; i < n; i++) if (s[i] != s[0]) {
        flag = 0; break;
    }
    if (flag) {
        ll ans = 1ll * n * (n + 1) / 2ll;
        printf("%I64d", ans % mod);
        return 0;
    }
    ll cnt1 = 1, cnt2 = 1;
    for (int i = 0; i < n; i++) if (s[i] == s[0]) cnt1++; else break;
    for (int i = n - 1; i > 0; i--) if (s[i] == s[n - 1]) cnt2++; else break;
    // printf("%I64d", cnt1 * cnt2 % mod);
    if (s[0] == s[n - 1]) {
        printf("%I64d", cnt1 * cnt2 % mod);
    } else {
        printf("%I64d", (cnt1 + cnt2 - 1) % mod);
    }
    return 0;
}