#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int len[maxn], vis[maxn], n, sum, tag;

int dfs(int tot, int pos, int rest){
    if (tot == tag) tot = 0, pos = 1;
    if (rest == 0) return 1;

    for(int i = pos; i <= n; i++) if (!vis[i] && tot + len[i] <= tag){
        vis[i] = 1;
        if (dfs(tot + len[i], i + 1, rest - 1))
            return 1;
        vis[i] = 0;
        if (tot == 0 || tot + len[i] == tag) return 0;
        while (i + 1 <= n && len[i + 1] == len[i]) i++;
    }
    return 0;
}

int main(){
    while (scanf("%d", &n) && n){
        sum = 0; int m = 0;
        for (int i = 1; i <= n; scanf("%d", &len[i]), sum += len[i], m = max(m, len[i]), i++);
        sort(len + 1, len + n + 1, greater<int>());
        
        ms(vis, 0);
        for (tag = m; tag <= sum; tag++){
            if (sum % tag) continue;
            if (dfs(0, 1, n)) break;
        }
        printf("%d\n", tag);
    }
    return 0;
}