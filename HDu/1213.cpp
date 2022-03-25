#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, pre[maxn];
void init(){
    for (int i = 0; i <= n; i++) pre[i] = i;
}
int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x); y = find(y);
    pre[x] = y;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        init();
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            join(x, y);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) if (pre[i] == i) ans++;
        printf("%d\n", ans);
    }
    return 0;
}