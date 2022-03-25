#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, m, vis[maxn], dir[maxn], ans[maxn], flag = 0;
vector<PII> edge[maxn];

void dfs(int u, int f, int d) {
    vis[u] = 1;
    // cout << u << endl;
    for (auto& x: edge[u]) {
        int v = x.first;
        ans[x.second] = d + 1;
        if (vis[v]) continue;
        dfs(v, u, d ^ 1);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back({v, 2 * i});
        edge[v].push_back({u, 2 * i + 1});
    }
    dfs(1, 0, 1);
    string s = "";
    for (int i = 1; i <= m; i++) {
        if (ans[2 * i] == ans[2 * i + 1]) {
            return puts("NO"), 0;
        }
        if (ans[2 * i] == 1 || ans[2 * i + 1] == 2) s += "0";
        else s += "1";
    }
    puts("YES"); cout << s << endl;
    // if (flag) puts("NO");
    // else {
    //     puts("YES");
    //     for (int i = 1; i <= m; i++) if (ans[2 * i] == 1 || ans[2 * i + 1] == 2) putchar('0'); else putchar('1');
    // }
    return 0;
}