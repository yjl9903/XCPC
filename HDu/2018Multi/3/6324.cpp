#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, w[maxn], vis[maxn], s[2], mark;

void dfs(int p, int d){
    vis[p] = 1; s[d] ^= w[p];
    for (int i = 0; i < edge[p].size(); i++){
        int v = edge[p][i]; 
        if (vis[v]) continue;
        dfs(v, d ^ 1);
    }
}
int dfs2(int p, int d){
    vis[p] = 1;
    if (d == 0){
        s[0] ^= w[p]; s[1] ^= w[p];
        if (s[0] > s[1]) return true;
        else if (s[0] == s[1]) mark = 1;
    }
    for (int i = 0; i < edge[p].size(); i++){
        int v = edge[p][i]; 
        if (vis[v]) continue;
        if (dfs2(v, d ^ 1)) return true;
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(vis, 0);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &w[i]), edge[i].clear();
        for (int i = 1; i < n; i++){
            int x, y; scanf("%d%d", &x, &y);
            edge[x].push_back(y);
            edge[y].push_back(x);
        }
        s[0] = s[1] = 0;
        dfs(1, 0);
        int flag;
        if (s[0] != s[1]) flag = 1;
        else{
            ms(vis, 0); mark = 0;
            int t = dfs2(1, 0);
            if (t) flag = 1;
            else if (s[0] == s[1] || mark) flag = 0;
            else if (s[0] < s[1]) flag = -1;
        }
        if (flag == 1){
            puts("Q");
        }
        else if (flag == 0){
            puts("D");
        }
        else if (flag == -1){
            puts("T");
        }
    }
    return 0;
}