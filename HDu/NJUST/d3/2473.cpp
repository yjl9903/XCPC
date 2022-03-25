#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, m;

int pre[maxn], id = 0;
bool vis[maxn];
void init(){
    id = n + n; ms(vis, 0);
    for (int i = 0; i < n; i++) pre[i] = i + n;
    for (int i = n; i < n + n; i++) pre[i] = i;
}
int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x); y = find(y);
    if (x != y) pre[y] = x;
}
void del(int x){
    pre[x] = id; pre[id] = id++;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d", &n, &m)){
        if (n == 0 && m == 0) break;
        init();
        char cmd[5]; int x, y;
        while (m--){
            scanf("%s", cmd);
            if (cmd[0] == 'M'){
                scanf("%d%d", &x, &y); join(x, y);
            }
            else if (cmd[0] == 'S'){
                scanf("%d", &x); del(x);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++){
            int x = find(i);
            if (!vis[x]){
                ans++; vis[x] = 1;
            }
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}