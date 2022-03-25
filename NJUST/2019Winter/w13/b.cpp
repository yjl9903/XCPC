#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;
const int maxg = 100 + 5;

vector<int> edge[maxn];
int n, m, k, s, a[maxn];

int dis[maxg][maxn];
void bfs(int s, int* dis) {
    queue<int> q; q.push(s); dis[s] = -1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int& v: edge[u]) {
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    // for (int i = 1; i <= n; i++) cout << dis[i] << ' '; cout << endl;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &s);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), edge[a[i] + n].push_back(i);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        // edge[a[u] + n].push_back(u);
        // edge[a[v] + n].push_back(v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = n + 1; i <= n + k; i++) {
        for (int j = 1; j <= n + k; j++) dis[i - n][j] = -1;
        bfs(i, dis[i - n]);

    }
    for (int i = 1; i <= n; i++) {
        ll sum = 0; vector<int> v;
        for (int j = 1; j <= k; j++) v.push_back(dis[j][i]);
        sort(v.begin(), v.end());
        for (int i = 0; i < s; i++) sum += v[i];
        printf("%I64d ", sum);
    }
    return 0;
}