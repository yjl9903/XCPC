#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 30000 + 5;

int pre[maxn], n, m;
void init(){
    for (int i = 0; i < n; i++)
        pre[i] = i;
}
int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x); y = find(y);
    pre[x] = y;
}

int main(){
    while (scanf("%d%d", &n, &m)){
        if (n == 0 && m == 0) break;
        init();
        for (int i = 0; i < m; i++){
            int k = 0; scanf("%d", &k);
            int s = 0; 
            if (k) scanf("%d", &s);
            for (int i = 1, x; i < k; i++){
                scanf("%d", &x);
                join(s, x);
            }
        }
        int res = 0, t = find(0);
        for (int i = 0; i < n; i++){
            // printf("%d ", find(i));
            if (find(i) == t)
                res++;
        }
        // printf("\n");
        printf("%d\n", res);
    }
    return 0;
}