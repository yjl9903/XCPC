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

vector<PII> edge[maxn];
int n, q, a[maxn], bag[1 << 22];

void dfs(int u, int f) {
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        a[v] = a[u] ^ x.second;
        bag[a[v]]++;
        dfs(v, u);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ms(bag, 0); for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        a[1] = 0; bag[0]++;
        dfs(1, 0);
        // for (int i = 1; i <= n; i++) cout << a[i] << endl;
        // cout << endl;
        scanf("%d", &q); int s;
        while (q--) {
            scanf("%d", &s);
            ll ans = 0;
            for (int i = 1; i <= n; i++) {
                ans += bag[a[i] ^ s];
                if (s == 0) ans--;
            }
            ans /= 2; if (s == 0) ans += n;
            printf("%lld\n", ans);
        }
    }
    return 0;
}