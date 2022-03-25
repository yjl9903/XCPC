#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int maxt = 200;

double f[20][maxt + 5], p[20], p2[20];
int n, a[20];

double qpow(double x, int n){
    double r = 1.0;
    while (n){
        if (n & 1) r = r * x;
        n >>= 1; x *= x;
    }
    return r;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 0; i < n; i++){
            scanf("%d%lf", a + i, p + i); p2[i] = 1.0;
        }
        // int maxt = 1200;
        if (n == 1){
            puts("1.000000"); continue;
        }
        for (int t = 1; t <= maxt; t++){
           for (int i = 0; i < n; i++){
                p2[i] = qpow(p[i], t);
                f[i][t] = qpow(1 - p2[i], a[i]);
           }  
        }
        for (int i = 0; i < n; i++){
            double ans = 0.0;
            for (int t = 1; t < maxt; t++){
                double g = 1.0;
                for (int j = 0; j < n; j++){
                    if (i == j) g *= (f[j][t + 1] - f[j][t]);
                    else g *= f[j][t];
                }
                ans += g;
            }
            printf("%.6lf%c", ans, " \n"[i == n - 1]);
        }
    }
    return 0;
}