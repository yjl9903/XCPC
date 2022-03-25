#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{
    int to, w;
};
// vector<edge> v[maxn];
int n, m, k, vis[maxn];

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &k);
        // for (int i = 1; i <= n; i++) v[i].clear(); 
        ms(vis, 0);
        while (k--){
            int x, y, w; scanf("%d%d%d", &x, &y, &w);
            // v[x].push_back({y, w});
            vis[y] = max(vis[y], w);
        }
        ll res = 0;
        for (int i = 1; i <= m; i++){
            res += vis[i];
        }
        printf("Case #%d: %lld\n", ++kase, res);
    }
    return 0;
}