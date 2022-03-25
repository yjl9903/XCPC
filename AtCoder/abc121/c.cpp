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

int n, m;
PII a[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].first, &a[i].second);
    sort(a + 1, a + 1 + n, [](PII a, PII b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    ll ans = 0;
    for (int i = 1; i <= n && m > 0; i++) {
        if (m >= a[i].second) {
            ans += 1ll * a[i].first * a[i].second;
            m -= a[i].second;
        } else {
            ans += 1ll * a[i].first * m;
            m = 0;
        }
    }
    cout << ans << endl;
    return 0;
}