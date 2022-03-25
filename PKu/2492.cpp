#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 2000 + 5;

int pre[maxn], val[maxn], n, k;
void init(){
    for (int i = 0; i <= n; i++)
        pre[i] = i, val[i] = 0;
}
int find(int x){
    if (x == pre[x]){
        return x;
    }
    int t = find(pre[x]);
    val[x] = (val[x] == val[pre[x]] ? 0 : 1);
    // val[x] = (val[x] + val[pre[x]]) % 2;
    pre[x] = t;
    return t;
}
bool join(int x, int y){
    int xx = find(x), yy = find(y);
    if (xx == yy){
        if (val[x] == val[y])
            return false;
        return true;
    }
    pre[yy] = xx;
    val[yy] = (val[x] == val[y] ? 1 : 0);
    // val[yy] = (val[x] - val[y] + 1) % 2;
    return true;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &k);
        int x, y, flag = 0; init();
        while (k--){
            scanf("%d%d", &x, &y);
            if (!join(x, y))
                flag = 1;
        }
        printf("Scenario #%d:\n", ++kase);
        if (flag)
            printf("Suspicious bugs found!\n");
        else
            printf("No suspicious bugs found!\n");
        if (T) printf("\n");
    }
    return 0;
}