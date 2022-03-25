#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, p2, p3;

int main(){
    scanf("%lld%lld%lld", &n, &p2, &p3);
    if (n == 1 || n == 2) {
        ll res = p3;
        if (p2 < p3) res = p2;
        printf("%d\n", res);
        return 0; 
    }
    double a2 = p2 / 2.0, a3 = p3 / 3.0;
    ll res = 0;
    // printf("%lf %lf\n", a2, a3);
    if (a2 <= a3){
        res = 1ll * n / 2 * p2;
        if (n % 2){
            res = min(res + p2, res - p2 + p3);
        }
    }
    else if (a3 < a2){
        res = 1ll * n / 3 * p3;
        if (n % 3 == 1){
            res = min(min(res + p3, res + p2), res - p3 + 2 * p2);
        }
        else if (n % 3 == 2){
            res = min(res + p3, res + p2);
        }
    }
    printf("%lld\n", res);
    return 0;
}