#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int fac[maxn], n, cnt = 0;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        ll res = -1;
        if (n % 3 == 0){
            int a = n / 3;
            res = 1ll * a * a * a;
        }
        else if (n % 3 == 1){
            if (n % 4 == 0){
                int a = n / 4;
                res = 2ll * a * a * a;
            }
        }
        else {
            if (n % 4 == 0){
                int a = n / 4;
                res = 2ll * a * a * a;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}