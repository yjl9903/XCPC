#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, k, deg[maxn];

int pre[maxn];
void init(){
    for (int i = 1; i <= n; i++) pre[i] = i;
}
int find(int x){
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y){
    x = find(x); y = find(y);
    pre[x] = y;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &k);
        ms(deg, 0); init();
        for (int i = 0; i < m; i++){
            int x, y; scanf("%d%d", &x, &y);
            x++; y++;
            deg[x]++; deg[y]++;
            join(x, y);
        }
        int c = 0, res = 0;
        for (int i = 1; i <= n; i++) if (i == pre[i]) c++;
        for (int i = 1; i <= n; i++) res = max(deg[i], res);
        if (k > m - res) k = m - res;
        res = res + c - 1 + k;
        printf("%d\n", res);
    }
    return 0;
}