#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int l, r, a[maxn];
bool need[maxn][5 * maxn];

int nxt[maxn], vis[maxn];
int dfs(int p){
    for (int i = 0; i < r; i++){
        if (!need[p][a[i]] || vis[i]) continue;
        vis[i] = 1;
        if (nxt[i] == -1 || dfs(nxt[i])){
            nxt[i] = p;
            return true;
        }
    }
    return false;
}
int match(){
    int ans = 0; ms(nxt, -1);
    for (int i = 0; i < l; i++){
        ms(vis, 0);
        if (dfs(i)) ans++;
    }
    return ans;
}

int main(){
    while (~scanf("%d%d", &l, &r)){
        ms(need, 0);
        for (int i = 0; i < r; i++) scanf("%d", a + i);
        for (int c, x, i = 0; i < l; i++){
            scanf("%d", &c);
            while (c--){
                scanf("%d", &x);
                need[i][x] = 1;
            }
        }
        printf("%d\n", match());
    }
    return 0;
}