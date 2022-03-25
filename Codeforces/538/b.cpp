#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, m, k, a[maxn], vis[maxn];
vector<PII> v;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), v.push_back({a[i], i});
    sort(v.begin(), v.end()); reverse(v.begin(), v.end());
    ll ans = 0;
    for (int i = 0; i < m * k; i++) ans += v[i].first, vis[v[i].second] = 1;
    printf("%I64d\n", ans);
    int c = 0, t = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) continue;
        c++;
        if (c == m) {
            printf("%d ", i); c = 0; t++;
            if (t == k - 1) break;
        }
    }
    return 0;
}