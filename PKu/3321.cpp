#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, index, tree[maxn], a[maxn], low[maxn], high[maxn];
// vector<int> line[maxn];
struct edge{int to, nxt;}f[maxn];
int cnt, head[maxn];
void add(int x, int y){
    f[++cnt].to = y; f[cnt].nxt = head[x]; head[x] = cnt;
}

void dfs(int p){
    low[p] = ++index;
    // for (int i = 0; i < line[p].size(); i++){
    //     dfs(line[p][i]);
    // }
    for (int i = head[p]; i; i = f[i].nxt){
        dfs(f[i].to);
    }
    high[p] = index;
}
inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i <= n){
        tree[i] += x;
        i += lowbit(i);
    }
}
inline int query(int i){
    int s = 0;
    while (i > 0){
        s += tree[i];
        i -= lowbit(i);
    }
    return s;
}

int main(){
    while (~scanf("%d", &n)){
        // for (int i = 1; i <= n; i++) line[i].clear();
        cnt = 0; ms(head, 0);
        for (int i = 1; i < n; i++){
            int x, y; scanf("%d%d", &x, &y);
            // line[x].push_back(y);
            add(x, y);
        }
        char cmd[5];
        index = 0; fill(a, a + 1 + n, 1); ms(tree, 0);
        for (int i = 1; i <= n; i++) update(i, 1);
        dfs(1);
        scanf("%d", &m);
        while (m--){
            int x; 
            scanf("%s", cmd);
            if (cmd[0] == 'Q'){
                scanf("%d", &x);
                // int ans = query(low[x], high[x], 1, n, 1);
                int ans = query(high[x]) - query(low[x] - 1);
                printf("%d\n", ans);
            }
            else if (cmd[0] == 'C'){
                scanf("%d", &x);
                int d;
                if (a[x] == 1) d = -1, a[x] = 0;
                else if (a[x] == 0) d = 1, a[x] = 1;
                // update(low[x], d, 1, n, 1);
                update(low[x], d);
            }
        }   
    }
    return 0;
}