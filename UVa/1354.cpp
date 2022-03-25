#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5 + 5;

struct node{
    int w = 0;
    double l = 0, r = 0;
}tree[1 << maxn];

int s, w[maxn], vis[1 << maxn], cnt;
double r, res = 0;

void dfs(int d){
    if (d >= s) return;
    for (int i = 1; i <= s + cnt; i++)
        if (!vis[i])
            for (int j = 1; j <= s + cnt; j++){
                // printf("%lf\n", 1 + max(tree[i].l, tree[j].l - 1) + max(tree[j].r, tree[i].r - 1));
                if (i != j && !vis[j] && 1 + max(tree[i].l, tree[j].l - 1) + max(tree[j].r, tree[i].r - 1) < r){
                    // printf("%d:%d  %d:%d\n", i, tree[i].w, j, tree[j].w);
                    // printf("%d\n%d:%lf %lf\n%d:%lf %lf\n", d, i, tree[i].l, tree[i].r, j, tree[j].l, tree[j].r);
                    // printf("%lf\n", 1 + max(tree[i].l, tree[j].l - 1) + max(tree[j].r, tree[i].r - 1));
                    if (d == s - 1)
                        res = max(res, 1 + max(tree[i].l, tree[j].l - 1) + max(tree[j].r, tree[i].r - 1));
                    vis[i] = vis[j] = 1;
                    int idx = ++cnt;
                    tree[s + idx].w = tree[i].w + tree[j].w;
                    // printf("%d\n", tree[idx].w);
                    double L = double(tree[j].w) / double(tree[s + idx].w), R = double(tree[i].w) / double(tree[s + idx].w);
                    tree[s + idx].l = max(tree[i].l + L, tree[j].l - 1 + L);
                    tree[s + idx].r = max(tree[j].r + R, tree[i].r - 1 + R);
                    // printf("%lf %lf\n", tree[s + idx].l, tree[s + idx].r);
                    vis[s + idx] = 0;
                    dfs(d + 1);
                    vis[s + cnt--] = 1;
                    vis[i] = vis[j] = 0;
                }
            }
                
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lf%d", &r, &s);
        for (int i = 1; i <= s; scanf("%d", &w[i++]));

        cnt = 0; res = -1; ms(vis, 0); ms(tree, 0);
        for (int i = 1; i <= s; i++){
            tree[i].w = w[i];
            tree[i].l = tree[i].r = 0;
        }
        
        dfs(1);
        if (s == 1) printf("0.0000000000000000\n");
        else if (res == -1)  printf("-1\n");
        else printf("%.15lf\n", res);
    }
    return 0;
}