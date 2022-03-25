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

int n, a[maxn], cnt[maxn], vis[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++;
    for (int i = 1; i + 1 < maxn; i++) {
        if (!cnt[i]) continue;
        if (i > 1 && !vis[i - 1]) vis[i - 1] = 1, cnt[i]--;
        if (!cnt[i]) continue;
        if (!vis[i]) vis[i] = 1, cnt[i]--;
        if (!cnt[i]) continue;
        if (!vis[i + 1]) vis[i + 1] = 1, cnt[i]--;
    }
    int ans = 0;
    for (int i = 1; i < maxn; i++) ans += vis[i];
    cout << ans;
    return 0;
}