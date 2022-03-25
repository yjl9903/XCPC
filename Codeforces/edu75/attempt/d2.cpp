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
const int maxn = 200000 + 5;

struct BIT {
    int n, a[maxn << 1];
    void clear(int nn) {
        n = nn;
        for (int i = 0; i <= n; i++) a[i] = 0;
    }
    void update(int i, int x) {
        for (; i <= n; i += i & -i) a[i] += x;
    }
    int query(int i) {
        int r = 0;
        for (; i; i -= i & -i) r += a[i];
        return r;
    }
} f;

int n; ll s, suf[maxn];
PII a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%I64d", &n, &s);
        vector<int> lsh;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].first, &a[i].second);
            lsh.push_back(a[i].first);
            lsh.push_back(a[i].second);
        }
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        f.clear(lsh.size() + 1);
        auto id = [&](int x) {
            return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
        };
        sort(a + 1, a + 1 + n);
        suf[n + 1] = 0;
        for (int i = n; i >= 1; i--) suf[i] = suf[i + 1] + a[i].first;
        ll ans = a[n / 2 + 1].first;
        for (int i = 1; i <= n / 2; i++) {
            f.update(id(a[i].second), 1);
        }
        for (int i = n / 2 + 1; i <= n; i++) {
            ll tot = suf[i + 1];

            
        }
        printf("%I64d\n", ans);
    }
    return 0;
}