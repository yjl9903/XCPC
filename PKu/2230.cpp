#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;

vector<int> edge[maxn], vis[maxn], ans;
int n, m;

void dfs(int u){
    for (int i = 0; i < edge[u].size(); i++){
        int v = edge[u][i];
        if (vis[u][i]) continue;
        vis[u][i] = 1;
        dfs(v);
    }
    ans.push_back(u);
}

int main(){ 
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        edge[x].push_back(y); edge[y].push_back(x);
        vis[x].push_back(0); vis[y].push_back(0);
    }
    dfs(1);
    reverse(ans.begin(), ans.end());
    // printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) printf("%d\n", ans[i]);
    return 0;
}