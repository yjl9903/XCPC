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
const int maxn = 500000 + 5;

int n, m, vis[maxn], u[maxn], v[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= 3 * n; i++) vis[i] = 1;
        vector<int> ans;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", u + i, v + i);
            if (vis[u[i]] && vis[v[i]]) {
                vis[u[i]] = 0; vis[v[i]] = 0;
                ans.push_back(i);
            }
        }
        if ((int)ans.size() >= n) {
            ans.resize(n);
            puts("Matching");
            for (int x: ans) printf("%d ", x);
            puts("");
        } else {
            puts("IndSet");
            for (int i = 1, c = 0; i <= 3 * n && c < n; i++) {
                if (vis[i]) {
                    c++;
                    printf("%d ", i);
                }
            }
            puts("");
        }
    }
    return 0;
}