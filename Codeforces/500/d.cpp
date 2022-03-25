#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int pre[2 * maxn], n, m, q;

int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}

int main(){
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i <= n + m; i++) pre[i] = i;
    while (q--){
        int x, y; scanf("%d%d", &x, &y);
        x = find(x); y = find(y + n); pre[x] = y;
    }
    int ans = 0;
    for (int i = 1; i <= n + m; i++) if (pre[i] == i) ans++;
    printf("%d", ans - 1);
    return 0;
}