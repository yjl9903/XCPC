#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

// vector<int> edge[maxn];
int n, m, k, q;
int G[505][505];
ll c[maxn];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    scanf("%d", &q);
    while (q--) {
        set<ll> st;
        for (int i = 1; i <= n; i++) scanf("%lld", c + i), st.insert(c[i]);
        if ((int)st.size() != k) puts("No");
        else {
            int flag = 0;
            for (int i = 1; i <= n && !flag; i++) for (int j = 1; j <= n; j++) if (G[i][j]) {
                if (c[i] == c[j]) {
                    flag = 1; break;
                }
            }
            if (flag) puts("No");
            else puts("Yes");
        }
    }
    return 0;
}