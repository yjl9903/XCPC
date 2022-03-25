#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, deg[maxn], tag[maxn];

int dfs(int u, int f) {
    if (tag[u]) return 0;
    if (deg[u] == 2) {
        for (int& v: edge[u]) {
            if (v == f) continue;
            if (dfs(v, u)) {
                tag[u] = 1;
                return 1;
            } else return 0;
        }
    }
    return tag[u] = 1; 
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
            deg[u]++; deg[v]++;
        }
        vector<int> leaf, ans; int cnt = 0;
        for (int i = 1; i <= n; i++) if (deg[i] == 1) leaf.push_back(i); else if (deg[i] == 2) cnt++;
        if (cnt + 2 == n) {
            printf("1\n%d\n", leaf[0]);
            for (int i = 1; i <= n; i++) {
                deg[i] = tag[i] = 0; edge[i].clear();
            }
            continue;
        }
        for (int& u: leaf) {
            if (dfs(edge[u].front(), u)) {

            } else {
                ans.push_back(u);
            }
        }
        printf("%d\n", ans.size());
        for (int i = 0; i < ans.size(); i++) {
            if (i) putchar(' ');
            printf("%d", ans[i]);
        }
        puts("");
        for (int i = 1; i <= n; i++) {
            deg[i] = tag[i] = 0; edge[i].clear();
        }
    }
    return 0;
}