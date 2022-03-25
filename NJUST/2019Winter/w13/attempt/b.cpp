#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;
const int maxg = 100 + 5;

int n, m, k, s, a[maxn];
int G[maxg][maxg];

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &s);
    for (int i = 1; i <= k; i++) for (int j = 1; j <= k; j++) G[i][j] = mod;
    for (int i = 1; i <= k; i++) G[i][i] = 0;
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (a[u] == a[v]) continue;
        G[a[u]][a[v]] = G[a[v]][a[u]] = 1;
    }
    // for (int l = 1; l <= k; l++) for (int i = 1; i <= k; i++) for (int j = 1; j <= k; j++) {
    //     if (G[i][j] > G[i][l] + G[l][j]) {
    //         G[i][j] = G[i][l] + G[l][j];
    //     }
    // }
    for (int i = 1; i <= n; i++) {
        ll sum = 0; vector<int> v;
        for (int j = 1; j <= k; j++) v.push_back(G[a[i]][j]);
        sort(v.begin(), v.end());
        for (int i = 0; i < s; i++) sum += v[i];
        printf("%I64d ", sum);
    }
    return 0;
}