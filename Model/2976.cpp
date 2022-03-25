// PKu2976 Dropping tests
// 01分数规划

#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const double eps = 1e-7;

int n, k, a[maxn], b[maxn];
double d[maxn];

bool cal(double m){
    for (int i = 0; i < n; i++) d[i] = 1.0 * a[i] - m * b[i];
    sort(d, d + n);
    double s = 0;
    for (int i = k; i < n; i++) s += d[i];
    return s > 0;
}

int main(){
    while (~scanf("%d%d", &n, &k)){
        if (!n && !k ) return 0;
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (int i = 0; i < n; i++) scanf("%d", &b[i]);
        double l = 0, r = 1;
        while (r - l > eps){
            double m = (r + l) / 2;
            if (cal(m)) l = m;
            else r = m;
        }
        printf("%.0f\n", 100 * l);
    }
    return 0;
}