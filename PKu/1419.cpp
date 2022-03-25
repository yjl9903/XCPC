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
const int maxn = 100 + 5;

int n, m, p[maxn], vis[maxn], G[maxn][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            G[u][v] = G[v][u] = 1;
        }
        for (int i = 1; i <= n; i++) p[i] = i;
        int T = 10000, ans = 0;
        vector<int> rec;
        while (T--) {
            random_shuffle(p + 1, p + 1 + n);
            ms(vis, 0);
            vector<int> v; 
            int res = 1; vis[1] = 1;
            v.push_back(p[1]);
            for (int i = 2; i <= n; i++) {
                int flag = 1;
                for (int j = 1; j < i; j++) {
                    if (vis[j] && G[p[i]][p[j]]) {
                        flag = 0; break;
                    }
                }
                if (flag) {
                    v.push_back(p[i]);
                    vis[i] = 1; res++;
                }
            }
            if (res > ans) {
                ans = res; rec = v;
            }
        }
        printf("%d\n", ans);
        for (int i = 0; i < (int)rec.size(); i++) {
            if (i) putchar(' ');
            printf("%d", rec[i]);
        }
        puts("");
    }
    return 0;
}