#include <cstdio>
using namespace std;
const int maxn = 1000 + 5;

int pre[maxn], N, Q;
void init(){
    for (int i = 0; i < maxn; i++)
        pre[i] = i;
}
int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x); y = find(y);
    pre[y] = x;
}
int main(){
    init();
    scanf("%d%d", &N, &Q);
    int cmd, x, y;
    while (Q--){
        scanf("%d%d%d", &cmd, &x, &y);
        if (cmd == 1)
            join(x, y);
        else if (cmd == 2)
            printf("%s\n", (find(x) == find(y) ? "Yes" : "No"));
    }
    return 0;
}