#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long LL;
const int maxn = 10000000 + 5;

unsigned A, B, C, x, y, z, a[maxn];
int n;

unsigned init(){
    LL t;
    x ^= x << 16; x ^= x >> 5; x ^= x << 1;
    t = x; x = y; y = z;
    return z = t ^ x ^ y;
}
LL gcd(LL a, LL b){
    return b ? gcd(b, a % b) : a;
}
LL lcm(LL a, LL b){return 1ull * a / gcd(a, b) * 1ull * b;}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%u%u%u", &n, &A, &B, &C);
        x = A; y = B; z = C;
        for (int i = 0; i < n; i++) a[i] = init();
        int sta = max(n - 100, 0);
        nth_element(a, a + sta, a + n);
        LL res = 0;
        for (int i = sta; i < n; i++){
            for (int j = i + 1; j < n; j++){
                res = max(res, lcm(a[i], a[j]));
            }
        }
        printf("Case #%d: %llu\n", ++kase, res);
    }
    return 0;
}