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
const int maxn = 1000000 + 5;

int n, a[maxn], pre[maxn], suf[maxn];
char s[maxn];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i < n; i++) {
        if (s[i] == 'v' && s[i + 1] == 'v') a[i] = 1;
    }
    for (int i = 1; i <= n; i++) pre[i] = a[i] + pre[i - 1];
    for (int i = n; i >= 1; i--) suf[i] = a[i] + suf[i + 1];
    ll ans = 0;
    for (int i = 3; i + 2 <= n; i++) {
        if (s[i] == 'v') continue;
        ans += 1ll * pre[i - 1] * suf[i + 1];
    }
    cout << ans;
    return 0;
}