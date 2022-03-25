#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5000 + 5;

int n;
struct node{
    int l; int r; int idx;
}x[maxn], y[maxn];
bool cmp(const node& a, const node& b){
    return a.r < b.r || (a.r == b.r && a.l < b.l);
}
int a[maxn], b[maxn], vis[maxn];

int main(){
    while (~scanf("%d", &n) && n){
        for (int i = 0; i < n; i++){
            scanf("%d %d %d %d", &x[i].l, &y[i].l, &x[i].r, &y[i].r);
            x[i].idx = i; y[i].idx = i;
        }
        sort(x, x + n, cmp); sort(y, y + n, cmp);
        int flag = 0; ms(vis, 0);
        for (int i = 0; i < n; i++){
            int t = x[i].l;
            while (vis[t] && t <= x[i].r) t++;
            if (t > x[i].r){
                flag = 1; break;
            }
            vis[t] = 1;
            a[x[i].idx] = t;
        }
        if (flag){
            printf("IMPOSSIBLE\n"); continue;
        }
        ms(vis, 0);
        for (int i = 0; i < n; i++){
            int t = y[i].l;
            while (vis[t] && t <= y[i].r) t++;
            if (t > y[i].r) {
                flag = 1; break;
            }
            vis[t] = 1;
            b[y[i].idx] = t;
        }
        if (flag){
            printf("IMPOSSIBLE\n"); continue;
        }
        for (int i = 0; i < n; i++){
            printf("%d %d\n", a[i], b[i]);
        }
    }
    return 0;
}