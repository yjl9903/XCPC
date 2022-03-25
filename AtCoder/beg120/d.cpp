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
const int maxn = 100000 + 5;

int n, m, a[maxn], b[maxn];

int pre[maxn], siz[maxn];
int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) pre[i] = i, siz[i] = 1;
    for (int i = 1; i <= m; i++) scanf("%d%d", a + i, b + i);
    ll ans = 1ll * n * (n - 1) / 2;
    vector<ll> v;
    for (int i = m; i >= 1; i--) {
        v.push_back(ans);
        int x = find(a[i]), y = find(b[i]);
        if (x == y) continue;
        ans -= 1ll * siz[x] * siz[y];
        pre[y] = x; siz[x] += siz[y] ;
    }
    for (int i = v.size() - 1; i >= 0; i--) printf("%lld\n", v[i]);
    return 0;
}