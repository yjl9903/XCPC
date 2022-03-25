#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 3000 + 5;

double a0, a1, c[maxn];
int n;

int main(){
    while (~scanf("%d", &n)){
        scanf("%lf%lf", &a0, &a1);
        if (n == 1){
            scanf("%lf", &c[0]);
            printf("%.2lf\n", (a0 + a1) / 2 - c[0]);
            continue;
        }
        for (int i = n; i > 0; i--){
            scanf("%lf", &c[i]);
        }
        double s = 0;
        for (int i = 1; i <= n; i++) s += 2 * i * c[i];
        double res = a1 + n * a0 - s;
        printf("%.2lf\n", res / (n + 1));
    }
    return 0;
}