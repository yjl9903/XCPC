#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, a[maxn][2], vis[maxn];
int pos[maxn][2];
vector<int> edge[maxn];
vector<int> ans;

void dfs(int u, int f) {
    for (int& v: edge[u]) {
        if (v == f || vis[v]) continue;
        ans.push_back(v); vis[v] = 1;
        dfs(v, u);
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++) {
        scanf("%d%d", &x, &y);
        pos[i][0] = x; pos[i][1] = y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs(1, 0);
    if (ans[1] != pos[ans[0]][0] && ans[1] != pos[ans[0]][1]) reverse(ans.begin(), ans.end());
    // reverse(ans.begin(), ans.end());
    for (int& x: ans) printf("%d ", x);
    return 0;
}