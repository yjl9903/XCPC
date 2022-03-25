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
const int maxn = 100000 + 5;

int n;
ll f[20], g[20];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 10; i++) f[i] = -1;
    for (int i = 1; i <= n; i++) {
        for (int i = 0; i <= 10; i++) g[i] = f[i];
        int k, c, d; scanf("%d", &k);
        vector<ll> v[4];
        while (k--) {
            scanf("%d%d", &c, &d);
            v[c].push_back(d);
        }
        for (int i = 1; i <= 3; i++) sort(v[i].begin(), v[i].end(), [](ll a, ll b) { return a > b; });
        for (int i = 0; i <= 9; i++) {
            if (f[i] == -1) continue;
            for (int j = 1; j <= 3; j++) {
                if (v[j].empty()) continue;
                if (i == 9) g[0] = max(g[0], f[i] + 2ll * v[j].front());
                else g[i + 1] = max(g[i + 1], f[i] + v[j].front());
            }
            if ((int)v[1].size() >= 3) {
                if (i + 3 >= 10) g[i - 7] = max(g[i - 7], f[i] + 2ll * v[1][0] + v[1][1] + v[1][2]);
                else g[i + 3] = max(g[i + 3], f[i] + v[1][0] + v[1][1] + v[1][2]);
            }
            if ((int)v[1].size() >= 2) {
                if (i + 2 >= 10) g[i - 8] = max(g[i - 8], f[i] + 2ll * v[1][0] + v[1][1]);
                else g[i + 2] = max(g[i + 2], f[i] + v[1][0] + v[1][1]);
            }
            if ((int)v[1].size() >= 1 && (int)v[2].size() >= 1) {
                if (i + 2 >= 10) g[i - 8] = max(g[i - 8], f[i] + v[1][0] + v[2][0] + max(v[1][0], v[2][0]));
                else g[i + 2] = max(g[i + 2], f[i] + v[1][0] + v[2][0]);
            }
        }
        swap(f, g);
    }
    ll ans = 0;
    for (int i = 0; i <= 10; i++) ans = max(f[i], ans);
    cout << ans;
    return 0;
}