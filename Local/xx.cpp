#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int qpow(int x, int mod){
    int r = 1, a = 2;
    while (x){
        if (x & 1) r = (r * a) % mod;
        x >>= 1;
        a = (a * a) % mod;
    }
    return r;
}

int n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        if (n <= 200 || n >= 400) puts("5000");
        else {
            int x = qpow(n - 1, n);
            if (x == 1) puts("0");
            else printf("%d\n", n);
        }  
    }
    return 0;
}