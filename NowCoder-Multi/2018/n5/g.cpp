#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int c, n;

bool isprime(int x){
    if (x == 1 || x == 2 || x == 3) return 1;
    for (int i = 2; i * i <= x; i++) if (x % i == 0) return 0;
    return 1;
}
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }

int main(){
    scanf("%d%d", &c, &n);
    int a, b;
    ll res = -1;
    for (int i = 1; i * c <= n; i++){
        for (int j = i; j > 0; j--){
            if (gcd(i, j) == 1){
                res = max(res, 1ll * i * j);
                break;
            }
        }
    }
    if (res != -1) res *= 1ll * c * c;
    printf("%lld\n", res);
    return 0;
}