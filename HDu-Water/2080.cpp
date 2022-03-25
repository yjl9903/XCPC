#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

double x1, y1, x2, y2;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        double t = x1 * x2 + y1 * y2;
        double d1 = sqrt(x1 * x1 + y1 * y1); 
        double d2 = sqrt(x2 * x2 + y2 * y2);
        d2 *= d1;
        double r = t / d2;
        double res = acos(r) * 180.0 / 3.14159265 ;
        printf("%.2lf\n", res);    
    }
    return 0;
}