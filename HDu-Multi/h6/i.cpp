#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n, vis[maxn], ans[maxn];
PII g[maxn];

void dfs(int p){
    vis[p] = 1;
    if (g[p].second) {
        if (!vis[g[p].first]) {
            dfs(g[p].first);
            ans[p] = ans[g[p].first];
            if (p == ans[p]){
                ans[p] = -1;
            }
        }
        else if (!ans[g[p].first]) ans[p] = maxn;
        else {
            ans[p] = ans[g[p].first];
            if (p == ans[p]){
                ans[p] = -1;
            }
        }
    }
    else {
        ans[p] = g[p].first;
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n); char s[20]; int x;
        for (int i = 1; i <= n; i++) {
            scanf("%d%s", &x, s);
            // if (s[0] == 'v') g[i].second = 1;
            // else if (s[0] == 'w') g[i].second = 0;
            if (s[0] == 'v') g[i] = make_pair(x, 1);
            else if (s[0] == 'w') g[i] = make_pair(x, 0);
        }
        ms(vis, 0); ms(ans, 0);
        for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i);
        int res = 0;
        for (int i = 1; i <= n; i++) res += (ans[i] == -1);
        printf("0 %d\n", res);
    }
    return 0;
}