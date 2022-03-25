#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, a[maxn];
ll pre[maxn], dp[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pre[i] = pre[i - 1] + a[i];
    dp[n] = pre[n]; ll mx = pre[n];
    for (int i = n - 1; i >= 1; i--) dp[i] = mx, mx = max(mx, pre[i] - dp[i]);
    cout << dp[1] << endl;
    return 0;
}