#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const double delta = 0.998;
const double eps = 1e-15;

int n, x[maxn], y[maxn], w[maxn];
double ansx, ansy, ans = 1e18;

double cal(double a, double b){
    double ans = 0;
    for (int i = 0; i < n; i++){
        double dx = a - x[i], dy = b - y[i];
        ans += sqrt(dx * dx + dy * dy) * w[i];
    }
    return ans;
}

void get(){
    double x = ansx, y = ansy, t = 2000;
    while (t > eps){
        double tx = x + ((rand() << 1) - RAND_MAX) * t;
        double ty = y + ((rand() << 1) - RAND_MAX) * t;
        double now = cal(tx, ty), d = now - ans;
        if (d < 0){
            x = tx; y = ty;
            ansx = tx; ansy = ty; ans = now;
        }
        else if (exp(-d / t) * RAND_MAX > rand()) x = tx, y = ty;
        t *= delta;
    }
}

int main(){
    srand(23333333);
    scanf("%d", &n); double sx = 0, sy = 0;
    for (int i = 0; i < n; i++) scanf("%d%d%d", &x[i], &y[i], &w[i]), sx += x[i], sy += y[i];
    ansx = sx / (double)n; ansy = sy / (double)n;
    get(); get(); get(); get();
    printf("%.3lf %.3lf", ansx, ansy);
    return 0;
}