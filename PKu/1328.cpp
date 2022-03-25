#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const double eps = 1e-5;

int dcmp(double x){
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
int n, d, vis[maxn];
struct node{
    double l, r;
}a[maxn];
bool cmp(node a, node b){
    if (fabs(a.r - b.r) < eps) return a.l < b.l;
    return a.r < b.r;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d", &n, &d)){
        if (!n && !d) break;
        int flag = 0;
        for (int i = 0; i < n; i++){
            int x, y; scanf("%d%d", &x, &y);
            if (y > d || y < 0) flag = 1;
            double d1 = sqrt(d * d - y * y);
            a[i].l = x - d1, a[i].r = x + d1;
        }
        if (flag){
            printf("Case %d: -1\n", ++kase);
            continue;
        }
        sort(a, a + n, cmp); ms(vis, 0);
        int res = 0;
        for (int i = 0; i < n; i++) if (!vis[i]){
            vis[i] = 1;
            res++;
            for (int j = i + 1; j < n; j++) if (dcmp(a[i].r - a[j].l) >= 0) vis[j] = 1;
        }
        printf("Case %d: %d\n", ++kase, res);
    }
    return 0;
}