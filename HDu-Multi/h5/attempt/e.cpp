#include <cstdio>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
const double pi = acos(-1.0);
const double eps = 1e-8;

int m, r;

int dcmp(double x){
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &m, &r);
        double res = 2 * pi * r;
        for (int i = 0; i < m; i++){
            int x, y, d; scanf("%d%d%d", &x, &y, &d);
            double dis = sqrt(x * x + y * y);
            if (dcmp(dis + d - r) < 0 || dcmp(r + d - dis) <= 0) continue;
            double a1 = 2 * acos((r * r + dis * dis - d * d) / 2 / r / dis);
            double a2 = 2 * acos((d * d + dis * dis - r * r) / 2 / d / dis);
            res += a2 * d - a1 * r;
        }
        printf("%.10lf\n", res);
    }
    return 0;
}