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
const int maxn = 200000 + 5;

int n, k, d[maxn], cnt[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", d + i), cnt[d[i] % k]++;
    int ans = 0;
    for (int i = 0; 2 * i <= k; i++) {
        if (2 * i == k || i == 0) ans += cnt[i] / 2 * 2;
        else ans += 2 * min(cnt[i], cnt[k - i]);
    }
    cout << ans << endl;
    return 0;
}