#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const ll mod = 998244353;

int n, m, cnt[maxn]; char a[maxn], b[maxn];

int main(){
    scanf("%d%d%s%s", &n, &m, a, b);
    if (b[0] == '1') cnt[0] = 1;
    for (int i = 1; i < m; i++) cnt[i] = cnt[i - 1] + b[i] - '0';
    ll tot = 1, ans = 0; reverse(a, a + n);
    for (int i = 0; i < n; i++, tot = tot * 2 % mod){
        if (i == m) break;
        if (a[i] == '0') continue;
        ans += tot * cnt[m - i - 1] % mod; ans %= mod;
    }
    printf("%I64d", ans % mod);
    return 0;
}