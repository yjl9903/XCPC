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

int n, b;
vector<int> edge[maxn];

int stk[maxn], tot, bel[maxn], bcnt, key[maxn];
void dfs(int u, int f) {
    int bot = tot;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        if (tot - bot >= b) {
            bcnt++; key[bcnt] = u;
            while (tot != bot) {
                bel[stk[tot--]] = bcnt;
            }
        }
    }
    stk[++tot] = u;
} 

int main() {
    scanf("%d%d", &n, &b);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    while (tot) bel[stk[tot--]] = bcnt;
    printf("%d\n", bcnt);
    for (int i = 1; i <= n; i++) printf("%d%c", bel[i], " \n"[i == n]);
    for (int i = 1; i <= bcnt; i++) printf("%d%c", key[i], " \n"[i == bcnt]);
    return 0;
}