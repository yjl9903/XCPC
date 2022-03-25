#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, m;
PII a[maxn], b[maxn];

struct BIT {
    int c[maxn];
    void update(int i, int x) {
        for (; i < maxn; i += i & -i) c[i] += x;
    }
    int query(int i) {
        int r = 0;
        for (; i; i -= i & -i) r += c[i];
        return r;
    }
} f, g;

int main() {
    scanf("%d%d", &n, &m);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        lsh.push_back(a[i].first);
        lsh.push_back(a[i].second);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &b[i].first, &b[i].second);
        lsh.push_back(b[i].first);
        lsh.push_back(b[i].second);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    auto gid = [&](int x) {
        return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    };
    ll ans = 1ll * n * m;
    for (int i = 1; i <= n; i++) {
        a[i].first = gid(a[i].first);
        a[i].second = gid(a[i].second);
    }
    for (int i = 1; i <= m; i++) {
        b[i].first = gid(b[i].first);
        b[i].second = gid(b[i].second);
        f.update(b[i].first, 1);
        g.update(b[i].second, 1);
    }
    for (int i = 1; i <= n; i++) {
        ans -= m - f.query(a[i].second);
        ans -= g.query(a[i].first - 1);
    }
    cout << ans;
    return 0;
}